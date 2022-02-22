# git status

步骤：（2）是新建的 ./bin也是新建的 ./bin里面有两个新建文本 

- git status 不能识别 未add的文件夹下的文件假如bin/ 下其他文件 运行git status 那么

![](https://raw.githubusercontent.com/mayuvix/Learning/master/img/202201141012619.png)



/bin 为 `git add bin` 

.gitignore 中 忽略了 ignore_file.txt

![image-20201116175257192](C:\Users\may-k\AppData\Roaming\Typora\typora-user-images\image-20201116175257192.png)

# git clean （-f -d -x）

-f表示文件 -d表示目录, 如果还要删除.gitignore中的文件那么再加上-x

- -f 清除untrack的文件（.gitignore生效,跳过.gitignore中指定的文件）
- -d 清除untrack的目录
- git clean -f -d或者git clean -fd都可以。

- fx  删除当前目录下所有没有 track 过的文件.// 不管是否是 .gitignore 文件里面指定的文件夹和文件

- fdx 整个 文件夹下的所有 untrack 文件以及文件加都会被删掉

  

### git不想每次都fetch all ref

- git 拉取指定远程仓库 git fetch origin .xxx.

![image-20210316104240967](C:\Users\may-k\AppData\Roaming\Typora\typora-user-images\image-20210316104240967.png)

- git checkout -b .xxx. origin/.xxx.


*checkout -b和不-b的区别??//*

- git 查看本地分支和远端分支的对应 git branch -vv

![image-20210316164833655](C:\Users\may-k\AppData\Roaming\Typora\typora-user-images\image-20210316164833655.png)

- *git rebase 只能在当前分支合并远端分支嘛?*

- ![image-20210316164141850](C:\Users\may-k\AppData\Roaming\Typora\typora-user-images\image-20210316164141850.png)



_____

创建分支： $ git branch mybranch
切换分支： $ git checkout mybranch
创建并切换分支： $ git checkout -b mybranch

更新master主线上的东西到该分支上：$git rebase master

切换到master分支：$git checkout master

更新mybranch分支上的东西到master上：$git rebase mybranch

提交：git commit -a

对最近一次commit的进行修改：git commit -a –amend

commit之后，如果想撤销最近一次提交(即退回到上一次版本)并本地保留代码：git reset HEAD^
合并分支：(merge from) $ git checkout master
$ git merge mybranch (merge from mybranch)
删除分支： $ git branch -d mybranch
强制删除分支： $ git branch -D mybranch
列出所有分支： $ git branch
查看各个分支最后一次提交： $ git branch -v

查看哪些分支合并入当前分支： $ git branch –merged

查看哪些分支未合并入当前分支： $ git branch –no-merged

更新远程库到本地： $ git fetch origin
推送分支： $ git push origin mybranch
取远程分支合并到本地： $ git merge origin/mybranch
取远程分支并分化一个新分支： $ git checkout -b mybranch origin/mybranch
删除远程分支：　　　　　　　　　　　　　　　　　$ git push origin :mybranch

rebase: $ git checkout mybranch
$ git rebase master (rebase from master)

举例： $ git checkout server
$ git rebase –onto master server client
$ git checkout master
$ git merge client (fostforward)
$ git rebase master server (checkout sever)
$ git merge server
$ git branch -d client
$ git branch -d server

---

### git fetch

git.exe fetch --progress -v "origin" master:remotes/origin/master

--progress ##打印进度 强制向标准输出流

-v --verbose ##详细点

* [参考](https://git-scm.com/docs/git-fetch#Documentation/git-fetch.txt---verbose)

####　远程拉取分支 fetch from origin



git.exe fetch -v --progress "origin" 

---



### 切换并创建远程分支对应的分支

git.exe checkout -b TextEditDlg_may-k remotes/origin/feature/TextEditDlg_may-k --



git reset --hard 1b45db1f7f413bfca639ae916ff131b13bebc65e && git -c submodule."View/Tools/GGPViewer/mlssdk".update=none submodule update --init --recursive



git.exe pull -v --progress "origin"



git.exe submodule update --init --recursive -- "gcmp_gst"(注意-- 后有空格)

git.exe submodule update --init --recursive -- "gdc-gcmp"



#### git rebase 

git rebase master origin/master

会切换到 origin/master分支

#### git remote() 本地记录的远端库

```
-r
-a
update ## 这个会将远端服务器的分支信息都拉取下来（fetch all reference？？有待验证）
```

 [git删除远程分支](https://www.cnblogs.com/smallredness/p/11205466.html)

```
git push origin --delete [branch_name]
```

### unset tracked branch

~~~

~~~

![image-20210517134652806](C:\Users\may-k\AppData\Roaming\Typora\typora-user-images\image-20210517134652806.png)

git.exe checkout -B release/release_v_0_14_0 remotes/origin/release/release_v_0_14_0 --

git checkout

https://www.jianshu.com/p/37f3a7e4a193

### 放弃merge 

```bash
git reset --hard HEAD --
```

HEAD is now at cd4c79e789 temp



git cherry-pick <commitId>

### 放弃本地修改

```bash
git checkout .
git checkout [filename]
```

###  rename branch 分支重命名

- in current branch 

```
git branch -m new_branch_name 
```

![image-20220119182107410](https://raw.githubusercontent.com/mayuvix/Learning/master/img/202201191821440.png)

- 当不在当前分支时

```
git branch -m old_branch_name new_branch_name
```

如果是已经推送到远端，应该怎么做呢？

#### 重命名远端分支（假设是在当前分支，并且远端分支与本地分支名是一致的）

- 重命名本地分支
  
  ```bash
  git branch -m new_branch_name
  ```
  
- 删除远程分支
  
  ```bash
  git push --delete origin old_branch_name
  ```
  
- 上传新命名的本地分支
  ```bash
  git push origin new_branch_name

- 关联修改后的本地分支与远程分支
  ``` bash
  git branch --set-upstream-to origin/new_branch_name
