#include <algorithm>
#include <iostream>
#include <functional>
#include <string>

int main() {
    std::string in = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                     " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua";
    std::string needle = "pisci";
   
//    timer_init(1);
//    timer_reset(0);
//    timer_start(0);
    
    auto it = std::search(in.begin(), in.end(),
                   std::boyer_moore_horspool_searcher(
                       needle.begin(), needle.end()));
    if(it != in.end())
        std::cout << "The string " << needle << " found at offset "
                  << it - in.begin() << '\n';
    else
        std::cout << "The string " << needle << " not found\n";

//    timer_stop(0);
//    printf("elapsed time %ld\n",timer_read(0));
//    printf("elapsed time %lf\n",(double)(timer_read(0)/1000000000.));
//    timer_finalize();
}
