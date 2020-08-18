# GameEngine
Hazel Engine

然后打入git命令，将代码库下载到本地。

C:\Users\Tim.AzureAD\Source\Repos>git clone https://github.com/netwarm007/GameEngineFromScratch.git
Cloning into 'GameEngineFromScratch'...
remote: Counting objects: 8, done.
remote: Compressing objects: 100% (8/8), done.
remote: Total 8 (delta 2), reused 0 (delta 0), pack-reused 0
Unpacking objects: 100% (8/8), done.
Checking connectivity... done.

C:\Users\Tim.AzureAD\Source\Repos>cd GameEngineFromScratch

C:\Users\Tim.AzureAD\Source\Repos\GameEngineFromScratch>
好了，这里就是将来代码生长的地方了。

为了能方便的回到每篇文章所对应的代码状态，我在每篇文章开始的时候给代码打个tag

C:\Users\Tim.AzureAD\Source\Repos\GameEngineFromScratch>git tag -a v0.0 -m "Initial"

C:\Users\Tim.AzureAD\Source\Repos\GameEngineFromScratch>git tag
v0.0
这样我们就可以通过下面的命令随时回到这个状态

C:\Users\Tim.AzureAD\Source\Repos\GameEngineFromScratch>git checkout -b article_1 v0.0
Switched to a new branch 'article_1'

C:\Users\Tim.AzureAD\Source\Repos\GameEngineFromScratch>git branch
* article_1
  master
新建的article_1这个branch就处于我们这篇文章开头的状态了。