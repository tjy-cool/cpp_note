#include <iostream>
#include <unistd.h>
#include "Timer.h"

using namespace std;

int main()
{
  Timer t = Timer();     // 定时器头t
  sleep(1);              // sleep 1s
  cout << "定时 : " << t.elapsed() << "毫秒·" << endl;
  cout << "定时 ：" << t.elapsed_nano()  << "纳秒" << endl;
  cout << "定时 ：" << t.elapsed_micro() << "微妙" << endl;
  cout << "定时 ：" << t.elapsed_seconds() << "秒" << endl;
  cout << "定时 ：" << t.elapsed_minutes() << "分" << endl;
  cout << "定时 ：" << t.elapsed_hours() << "时" << endl;
  
  t.reset();
  cout << endl;
  cout << "定时器重新设置了" << endl;
  cout << "定时 : " << t.elapsed() << "毫秒·" << endl;
}
