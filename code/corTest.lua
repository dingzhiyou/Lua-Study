function CorTest(param1,parma2,param3,param4)
    print("prarm2:" ,param2)
    print("coroutine begin:",param1,param2,param3,param4)
---100,hello c++两个参数返回栈
    local re = coroutine.yield(100, "hello c++","this is end")
---re是lua_resume的参数
    print("coroutine continue: " .. re)
    Stop("stop func!","--------------------")
    print("coroutine continue after yield")
    print("coroutine end")
end
 
