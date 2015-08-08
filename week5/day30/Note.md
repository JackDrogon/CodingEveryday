git reset [--hard|soft|mixed|merge|keep] [<commit>或HEAD]
作用：将当前分支reset到指定的<commit>或者HEAD(默认为最新的一次提交，即重设到最新一次提交之前的版本)

备注：
       index，执行git add的操作，会对文件创建索引，所有被跟踪的文件索引会放入index，表示文件被修改待提交
       working tree，当前工作区，被修改但未被add的文件，存储在工作区
       ORIG_HEAD,用于指向前一个操作状态,每次的commit或者pull或者reset，git 都会把老的HEAD拷贝到.git/ORIG_HEAD，通过对ORIG_HEAD的引用可    以指向前一次的操作状态

1、hard(慎用)
重设index和working tree,所有改变都会被丢弃，包括文件的修改、新增、删除等操作，并把HEAD指向<commit>，
因此通过git log查看版本提交记录，被reset的版本记录会被丢弃，但可以通过git reflog查看

2、soft
不重设index和working tree,仅仅将HEAD指向<commit>,表示已经commit的文件会取消commit,
通过git status查看，文件会处于待commit状态“Changes to be committed”

3、mixed(默认)
重设index,但不重设working tree,表示已经被add的文件，被取消add，
通过git status查看，文件会处于待添加索引状态 “Changes not staged for commit”

4、merge
重设index，重设working tree中发生变化的文件，但是保留index和working tree不一致的文件

5、keep
重设index，重设working tree中发生变化的文件
