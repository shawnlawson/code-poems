//c++ rule30.cpp -o rule30
#include<iostream>
int i,j,l,r,o[80]={},t[80]={};
char c;
int main(){
  std::cout<<"enter character, then return >> ";
  std::cin>>c;
  o[39]=1;
  while(1){
    for(j=0;j<80;j++){
      if(j)     l=o[j-1]; else l=o[79];
      if(j!=79) r=o[j+1]; else r=o[0];
      if(o[j])
        if(l)   t[j]=0;   else t[j]=1;
      else
        if(l^r) t[j]=1;   else t[j]=0;
      std::cout<<((o[j]?" ":&c));
    }
    for(;--j>=0;) o[j]=t[j];
    std::cout.flush();
    usleep(50000);
  }
}