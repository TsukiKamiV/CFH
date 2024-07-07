
     while (fd >= 0) 循环 通常都不会跳出。是通过不断的循环，让ret满足条件后直接return
      1. gimme_current结束后，会返回current结果。
        1.1 出错了， current就为NULL， ret已经在gimme_current里好好的reset了， 直接返回ret
        1.2 没出错， 但是没东西可读了， 直接返回ret
        1.3 没出错， 读到东西了（或者有remainder存留），则current会承载着信息， 进入下一步 gimme_line
      2.
        2.1 如果在current里找到了'\n'，则拼接ret = ret + current的换行前部分，换行后部分留给remainder，返回ret
        2.2 如果在current里没找到'\n'，则拼接ret = ret + current，进入下一个 while (fd >= 0) 循环
        在2结束前的最后一句，current = NULL; 说明无论如何，current都是 while (fd >= 0) 循环中的变量，信息带不到下一次 while (fd >= 0) 循环。
        current的任务就是从步骤1中接手一次信息，在2中处理，信息的流向是ret，remainder，或both      
