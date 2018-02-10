// 2017/9/24
// 澤田優真
// サーバへメッセージを送信するクライアントプロセス
// ipアドレスは[ip addr]で調べる(分からない場合)

#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/fcntl.h>
#include <stdio.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h>
#include <unistd.h> 
#include <stdlib.h>


int main(int argc, char *argv[]){
  int sockfd;
  struct sockaddr_in client_addr;
  char *data[256];
  char *message[256];

  if(argc != 3){
    printf("IPアドレス,ポート番号　の順に引数を正しく指定してください\n"); //ip=172.21.34.109?
  }
  
  printf("文字を入力してください\n");     
  scanf("%s",data);
  
  //ソケットを生成 
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("client: socket");
    exit(1);

  }

  //構造体にサーバの情報を設定
  client_addr.sin_family = AF_INET;
  client_addr.sin_addr.s_addr = inet_addr(argv[1]);
  client_addr.sin_port = atoi(argv[2]);
  
  //サーバへ接続
  if (connect(sockfd, (struct sockaddr *)&client_addr, 
	      sizeof(client_addr)) < 0) {
    perror("client: connect");
    close(sockfd);
    exit(1);
  }
  
  //メッセージ送信
  if(write(sockfd, data, 256) < 0){
    perror("no send");
    exit(1);
  }

  //サーバからのメッセージ受信
  if(read(sockfd, message, 256) < 0){
    perror("no read");
    exit(1);
  }
  printf("%s\n",message);
  if(close(sockfd) < 0){
    perror("no close");
    exit(1);
  } 
  exit(0);
}
