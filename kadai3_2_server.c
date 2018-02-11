// 2018/2/11
// 1190326 澤田優真
// クライアントから送信されたメッセージを表示するサーバプログラム



#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int data_buf = 256;
static int message_buf = 256;
static int port = 10000;

void waiting(int sign){
  pid_t pids;
  int sig;
  while((pids=waitpid(-1,&sig,WNOHANG))>=0){
    printf("wait for %d \n",pids);
  }
}

int main(int argc, char *argv[]){

  int sockfd;
  int port_num;
  int new_sockfd;
  unsigned writer_len;
  char data[data_buf];
  char message[256] = "Thanks for message!!\n";
  struct sockaddr_in reader_addr;
  struct sockaddr_in writer_addr;
  pid_t pid;

  //message="accept OK!! \n";

  if(argc > 2 || argc == 0 ){
    printf("ポート番号を正しく指定してください\n");
    exit(1);
  }else if(argc == 1){
    printf("ポート番号が指定されなかったため, 10000に設定します\n");
    port_num = port;
  }else{
    port_num = atoi(argv[1]);
  }

  /* ソケットの生成 */

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }
  /* 通信ポート・アドレスの設定 */
  reader_addr.sin_family = AF_INET;
  reader_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  reader_addr.sin_port = htons(port_num);
  printf("Start-up\n");
  /* ソケットにアドレスを結びつける */
  if (bind(sockfd, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0) {
    perror("bind");
    exit(1);
  }
  /* コネクト要求をいくつまで待つかを設定 */
  if (listen(sockfd, 5) < 0) {
    perror("listen");
    close(sockfd);
    exit(1);
  }
  signal(SIGCHLD,waiting);
  while(1){
     /* コネクト要求を待つ */
    printf("waiting accept\n");
    if((new_sockfd = accept(sockfd,(struct sockaddr *)&writer_addr, &writer_len)) < 0){
      perror("accept");
      exit(1);
    }else{
      pid = fork();
      if(pid==0){
        //送られてきたメッセージを受信
        printf("child start\n");
        if(read(new_sockfd, &data, data_buf) < 0){
          perror("read");
          exit(1);
        }else{
          printf("Client : %s", data);
        }
        //受信完了のメッセージをクライアントへ送信
        if(write(new_sockfd, &message, message_buf) < 0){
          perror("send");
          exit(1);
        }
        //終了
        if(close(new_sockfd)< 0){
          perror("close");
          exit(1);
        }
      }else{
        if(close(new_sockfd)< 0){
          perror("close");
          exit(1);
        }
      }
    }
  }
  return 0;
}
