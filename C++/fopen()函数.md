fopen()函数主要做是：
1. 建立一个FILE对象。
2. 根据路径在外存中找到描述文件的对象，并根据所找到的对象的信息初始化FILE对象。
3. 返回FILE对象的指针。
从上可知，调用fopen()函数时，并未将文件的内容读到内存中，而是在文件系统中找到描述该文件的对象，并建立描述该文件的FILE对象。
fopen只是打开文件，还得用fread或其他读文件命令才能读入文件内容，操作顺序应该是打开文件--读入文件--关闭文件。

现在大多数的系统采用分页机制，在打开文件成功后，文件并没有加载进入内存，而是内核生成了一个文件描述符，文件描述符含有一个指向文件inode结构的指针，在这个结构中存有文件真正的节点信息和位置。当读取的时候，cpu首先判定需要读取的位置是否在内存上，如果再则直接读取（没有所谓的按行读取一说，按行读取不过是找文件中的换行标而已，当读到换行符的时候返回结果），如果不在内存上，则通过内存管理器进行加载，实际上，无论你是读取一个字符还是一行，加载的大小是固定的，比如系统机制是加载1M，当你文件大于1M时也只加载1M，当不够时全部加载。对不不同系统方式不同。（当然系统如果对读文件有特殊的优化也不同），当你读取之后，文件是继续留在内存还是释放，这里有另一套极其复杂的机制在管理。因为在你读第一行和第二行的时间里，还有许多事情在并发的执行。
————————————————
版权声明：本文为CSDN博主「missingu1314」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/missingu1314/article/details/8946346