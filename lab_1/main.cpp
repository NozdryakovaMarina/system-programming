//
// ROOT
// ├─── a_2.txt (символьная ссылка на b_3.txt)
// ├─── a_3.txt('pig') +
// ├─── a_1+
// │  └─── b_2.bin (жесткая ссылка на c_2.bin)
// │  └─── b_3.txt ('horse')+
// │  └─── b_1+
// │    └─── c_2.bin (293 байт, случайный)+
// └─── a_0+
//     └─── b_0+
//        ├─── c_0 (каталог)+
//        └─── c_1.txt ('parrot')+
// 


#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <filesystem>
#include <cstring>

using namespace std;
namespace fs = filesystem;


void createDir(const char* pathname){
    mkdir(pathname, S_IRWXO|S_IRWXU|S_IRWXG);
}

void createFile(const char* path, const char* content){
    int fd = open(path, O_CREAT | O_RDWR, S_IRWXO|S_IRWXU|S_IRWXG);

    if(fd < 0){
        cerr << "Can`t open file" << endl;
        exit(1);
    }

    write(fd, content, strlen(content));

    close(fd);
}

int main() {
    createDir("./ROOT");
    createDir("./ROOT/a_1");
    createDir("./ROOT/a_0");
    createDir("./ROOT/a_1/b_1");
    createDir("./ROOT/a_0/b_0");
    createDir("./ROOT/a_0/b_0/c_0");

    createFile("./ROOT/a_3.txt", "pig");
    createFile("./ROOT/a_1/b_3.txt", "horse");
    createFile("./ROOT/a_0/b_0/c_1.txt", "parrot");

    size_t size = 293;
    char* buffer = new char[size];
    int fd_c2 = open("./ROOT/a_1/b_1/c_2.bin", O_CREAT | O_RDWR, S_IRWXO|S_IRWXU|S_IRWXG);

    if(fd_c2 == -1){
        cerr << "Can't open file" << endl;
        exit(1);
    }

    for(size_t i = 0; i < size; ++i){
        buffer[i] = (char)(rand() % 256);
    }

    cout << "Size of c_2.bin " << write(fd_c2, buffer, size) << endl;

    close(fd_c2);

    int fd_a2 = open("./ROOT/a_2.txt", O_CREAT | O_RDWR, S_IRWXO|S_IRWXU|S_IRWXG);

    if(fd_a2 == -1){
        cerr << "Can`t open file" << endl;
        exit(1);
    }

    if(symlink("./ROOT/a_1/b_3.txt", "./ROOT/a_2.txt") == -1){
        cout << "Link error" << endl;
    }

    close(fd_a2);

    int fd_b2 = open("./ROOT/a_1/b_2.bin", O_CREAT | O_RDWR, S_IRWXO|S_IRWXU|S_IRWXG);

    if(fd_b2 == -1){
        cerr << "Can`t open file" << endl;
        exit(1);
    }

    if(link("./ROOT/a_1/b_1/c_2.bin", "./ROOT/a_1/b_2.bin") == -1){
        cout << "Link error" << endl;
    }

    close(fd_b2);

    return 0;
}