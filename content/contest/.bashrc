alias c='g++ -Wall -Wconversion -Wfatal-errors -g -std=c++17 \
	-fsanitize=undefined,address'
alias cphash='sed "s/\/\/.*//" | tr -d " \n\t\r" | md5sum | cut -c1-6'
# cat template.cpp | cphash
xmodmap -e 'clear lock' -e 'keycode 66=less greater' #caps = <>
