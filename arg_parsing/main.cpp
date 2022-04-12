/*
Usage:
./main -f abc -g def -a 2 -b 1
./main --f1 abc --f2 def --param1 2 --param2 1
*/
#include <iostream>
#include <cstdio>
#include <getopt.h> /*getopt_long*/

struct Params {
  std::string filename1;
  std::string filename2;
  int a;
  double b;
};

void parse_args(int argc, char* argv[], Params& params){
    
  static struct option long_options[] = {
    {"f1", required_argument, NULL, 'f'},
    {"f2", required_argument, NULL, 'g'},
    {"param1", required_argument, NULL, 'a'},
    {"param2", required_argument, NULL, 'b'},
    {NULL, 0, NULL, 0}
  };
  static char usage[] = "usage: %s --f1 fname-image-1 --f2 fname-image-2 --param1 1 --param2 2  \n";
  
  int opt;
  while(1){
    // the : means that there is a return value
    opt = getopt_long(argc, argv, "f:g:cha:b:", long_options, NULL);        
    if(opt == -1) /* Detect the end of the options. */
      break;
    
    switch(opt) {
      case 'f':
        params.filename1 = optarg;
        break;
      case 'g':
        params.filename2 = optarg;
        break;
      case 'a':
        params.a = std::atoi(optarg);
        break;
      case 'b':
        params.b = std::atof(optarg);
        break;                
      case 'h':
        std::fprintf(stderr, usage, argv[0]);                
        break;
      default:
        std::fprintf(stderr, usage, argv[0]); 
        abort();
    }
  }    
}    

auto main(int argc, char* argv[] ) -> int {
    
  Params params;
  parse_args(argc, argv, params);

  std::cout << params.filename1 << "\n";
  std::cout << params.filename2 << "\n";
  std::cout << params.a << "\n";
  std::cout << params.b << std::endl;

  return 0;
}