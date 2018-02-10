// 2017/9/24
// 澤田優真
// クライアントから送信されたメッセージを表示するサーバプロセス



#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

int main(int argc, char *argv[]){

  int sockfd;
  int new_sockfd;
  int writer_len;
  char data[256];
  char message[256] = "accept OK!! \n";
  struct sockaddr_in reader_addr; 
  struct sockaddr_in writer_addr;

  if(argc != 2){
    printf("ポート番号を正しく指定してください\n");
  }

  /* ソケットの生成 */

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("reader: socket");  }



  /* 通信ポート・アドレスの設定 */

  reader_addr.sin_family = AF_INET;
  reader_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  reader_addr.sin_port = atoi(argv[1]);

  printf("起動\n");

  /* ソケットにアドレスを結びつける */

  if (bind(sockfd, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0) {
    perror("reader: bind");
    exit(1);
  }

  /* コネクト要求をいくつまで待つかを設定 */

  if (listen(sockfd, 5) < 0) {
    perror("reader: listen");
    close(sockfd);
    exit(1);
  }


 
  while(1){
     /* コネクト要求を待つ */
    printf("waiting accept\n");
    if ((new_sockfd = accept(sockfd,(struct sockaddr *)&writer_addr, &writer_len)) < 0) {
      perror("reader: accept");
      exit(1);
    }

    //送られてきたメッセージを受信
    if(read(new_sockfd, &data, 256) < 0){
      perror("no read");
      exit(1);
    }

    printf("message is 「%s」 \n", data);

    //受信完了のメッセージをクライアントへ送信
    if(write(new_sockfd, &message, 256) < 0){
      perror("no send");
      exit(1);
    }
    
    //終了
    if(close(new_sockfd)< 0){
      perror("no close");
      exit(1);
    }
  }
  return 0;
}
