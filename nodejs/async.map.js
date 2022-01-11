// This function takes a contents object with a files array.
// The goal is to cache each file details in redis then replace
// the file's path with a secure, obscured url.

// Finally the contents object is returned with the updated array
// in place of the old one.

// async = require('async')
// uuid = require('node-uuid')
// redis.client = require('node-redis').createClient()

var transform = function(contents, done) {
	
	// generate a new auth id for the user and store it in redis with a ttl of 1 hour
	
	var authExpiry = 60 * 60 * 1000, // 1 hour
		authId = uuid.v4(), // unique request to ID the user
		authKey = 'file:auth:' + authId;
	
	redis.client.set(authKey, JSON.stringify({
		userId: req.user.id
	}));
	redis.client.expire(authKey, authExpiry);
	
	// function to send the secure file paths back to the user
	
	var sendContents = function(err, files) {
		if (err) return handleError(err);
		contents.files = files;
		done(contents);
	}
	
	// loop through the files array, caching each in redis (if it doens't exist)
	// and turning the file path into {authId}/{fileId}
	
	// async.map executes in parallel, see https://github.com/caolan/async#map
	// async.mapLimit and async.mapSeries are also available.
	
	async.map(contents.files, function(file, next) {
		
		// fileIds are cached in redis with the file path as the key
		var lookupKey = 'file:path:' + file.path;
		
		redis.client.get(lookupKey, function(err, fileId) {
			
			// bail if there was an error
			if (err) return next(err);
			
			if (fileId) {
			  // if we found a fileId, it is already in the cache.
			  // convert it to a string and use it.
				fileId = fileId.toString();
			} else {
			  // if we didn't, create a new id and cache the file details
				fileId = uuid.v4();
				redis.client.set('file:id:' + fileId, JSON.stringify(file));
				redis.client.set(lookupKey, fileId);
			}
			
			// rewrite the path of the file to {authId}/{fileId}
			file.path = authId + '/' + fileId;
			
			// continue
			next(false, file);
			
		});
		
	}, sendContents);
	
}