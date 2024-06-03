#include <stdio.h>
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include<iostream>
#include<string>
#include <assert.h>
using namespace std;

static int Stop(lua_State* L);


lua_State* CreateCoroutine(lua_State* gL, const char* corName);

static int resume2(lua_State *L, int status, lua_KContext ctx) {
    cout << "address:" <<L<< endl;
    cout << "Resuming coroutine2..." << endl;
    if (status != LUA_YIELD) {
        cout << "Error: Coroutine did not yield" << endl;
        return 0;
    }
    cout<<"resume2 :    "<<lua_gettop(L)<<endl;
    return 2;
}
//延续函数
static int resume(lua_State *L, int status, lua_KContext ctx) {
     cout << "address:" <<L<< endl;
    cout << "Resuming coroutine..." << endl;
    // 检查协程的状态
    if (status != LUA_YIELD) {
        cout << "Error: Coroutine did not yield" << endl;
        return 0;
    }
    cout<<"resume :    "<<lua_gettop(L)<<endl;
    // 获取协程返回值
    const char*  result = lua_tostring(L, -1);
    cout << "Received result from coroutine: " << result << endl;
    result = lua_tostring(L, -2);
    cout << "Received result from coroutine: " << result << endl;
    result = lua_tostring(L, -3);
    cout << "Received result from coroutine: " << result << endl;
    result = lua_tostring(L, -4);
    cout << "Received result from coroutine: " << result << endl;
      result = lua_tostring(L, -5);
    if(result) {
        cout<<result<<endl;
    }else {
        cout<<"no resault 5"<<endl;
    }
    
  
   lua_pushstring(L,"i am from resume func");
   cout<<"resume :    "<<lua_gettop(L)<<endl;
  
  
   lua_yieldk(L,10,0,resume2);
   
   return 0;
}


int main()
{

lua_State *L = luaL_newstate();
cout<<"-----1stack size: "<<lua_gettop(L)<<endl;
luaL_openlibs(L);
cout<<"-----openlibs stack size: "<<lua_gettop(L)<<endl;



if (luaL_dofile(L, "../../code/corTest.lua") != LUA_OK) {
    const char *error = lua_tostring(L, -1);
    printf("Error: %s\n", error);
}

lua_State* newL = lua_newthread(L);
cout<<"newL:"<<newL<<endl;
lua_register(newL,"Stop",Stop);
lua_getglobal(newL,"Stop");
cout<<"after getglobal push Stop func: "<<lua_gettop(L)<<endl;
lua_pushstring(newL,"i am push string");
lua_pushstring(newL,"i am push string2");
lua_pushstring(newL,"i am push string3");
lua_pushstring(newL,"i am push string4");
cout<<"put 4 args for Stop func : "<<lua_gettop(newL)<<endl;
int re = lua_resume(newL,L, 4);
if(re != LUA_YIELD)
    cout<<"ERROR"<<endl; 
cout<<"first yield return : "<<lua_gettop(newL)<<endl;
const char* str1 = lua_tostring(newL, 8);
const char* str2 = lua_tostring(newL, 7);
const char* str3 = lua_tostring(newL, 6);


cout<<"str1:"<<str1 << endl;
cout<<"str2:"<<str2 << endl;
if(str3 != nullptr) {
    cout<<"str3:"<<str3 << endl;
}else {
    cout<<"str3 is nullptr:"<< endl;
}


// 这次恢复协程时传入参数, 参数压栈, lua中就是对应返回值local re
lua_pushstring(newL,"===============");
lua_pushstring(newL,"===============");
  
cout<<"after push two equal symbol: "<<lua_gettop(newL)<<endl;
re = lua_resume(newL,L, 6);
assert(re == LUA_YIELD);
cout<<"re is : "<<re<<endl;


//assert(re == 0);
printf("after yield from resume: %d\n",lua_gettop(newL));
str1 = lua_tostring(newL, 6);
cout<<"str1:"<<str1<<endl;





re = lua_resume(newL,L, 100);
if(re == LUA_OK) {
    cout<<"OK"<<endl;
} 


//re = lua_resume(newL,L, 0); // 这里无法传值回去lua了,因为Stop的栈已经被释放 ,而是直接运行lua中Stop的后一句
//lua_close(L);
return 0;
}


static int Stop(lua_State* lp)
{
// 会传一个参数进来
cout<<"address:"<<lp<<endl;
printf("Stop func stack szie: %d\n",lua_gettop(lp));
const char* str1 = lua_tostring(lp, -1);
cout<<"top arg string ="<<str1<<endl;


lua_pop(lp,2);


lua_yieldk(lp,8,0,resume);





//cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
printf("=======Stop func stack szie: %d\n",lua_gettop(lp));

const char* str = lua_tostring(lp,-1);
printf("C Stop Func: %s\n", str);
//将这个值再次压入栈中
std::string str2 = "aaaaa";
lua_pushstring(lp,str2.c_str());
printf("Stop func stack szie: %d\n",lua_gettop(lp));
//Yields a coroutine.
//This function should only be called as the return expression of a C function, as follows:
return lua_yield(lp,2);
}


 

 