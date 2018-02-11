// 2018/2/11
// 1190326 澤田優真
// サーバへメッセージを送信するクライアントプログラム

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

static int data_buf = 256;
static int message_buf = 256;

int main(int argc, char *argv[]){
  int sockfd;
  struct sockaddr_in client_addr;
  char data[data_buf];
  char message[message_buf];
  if(argc != 3){
    printf("IPアドレス,ポート番号　の順に引数を正しく指定してください\n");
    exit(1);
  }

  //ソケットを生成
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }
  //構造体にサーバの情報を設定
  client_addr.sin_family = AF_INET;
  client_addr.sin_addr.s_addr = inet_addr(argv[1]);
  client_addr.sin_port = htons(atoi(argv[2]));
  //サーバへ接続
  if (connect(sockfd, (struct sockaddr *)&client_addr,sizeof(client_addr)) != 0){
    perror("connect");
    close(sockfd);
    exit(1);
  }
  printf("文字を入力してください\n");
  fgets(data, data_buf, stdin);
  int i = 0;
  while(1) {
    if(data[i] == '\n') {
      data[i] = '\n';
      data[i+1] = '\0';
      break;
    }
    i++;
  }
  //メッセージ送信
  if(write(sockfd, data, data_buf) < 0){
    perror("write");
    exit(1);
  }
  //サーバからのメッセージ受信
  if(read(sockfd, message, message_buf) < 0){
    perror("read");
    exit(1);
  }
  printf("%s\n",message);
  if(close(sockfd) < 0){
    perror("close");
    exit(1);
  }
  return 0;
}
