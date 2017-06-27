
#include "serial/serial.h"
#include "crc/crc.h"
#include <unistd.h>
#define BUFSIZE 16

int main(int argc, char **argv) {
  
  
    int fd, len;
    int error_cnt = 0;
    uint8_t buf[BUFSIZE], temp_buf[BUFSIZE],result_buf[BUFSIZE];
    
    char *msg ="We have open serial port: ";
    fd_set rds;
    char *openPort = argv[1];
    std::cout << "Open port:"<<openPort<<" ..." << std::endl;
    fd = open(openPort, O_RDWR | O_NOCTTY | O_NDELAY );
//    fd = open("/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0", O_RDWR | O_NOCTTY | O_NDELAY );
    //fd = open("/dev/ttyUSB0", 0 );
    if(fd < 0)
    {
	std::cout << "Open Error!" << std::endl;
        return 1;
    }
    memset(buf, 0, sizeof(buf));
    memset(temp_buf, 0, sizeof(temp_buf));
    memset(result_buf, 0, sizeof(temp_buf));
    UART0_Init(fd,115200,0,8,1,'N');
    std::cout << msg <<openPort<<" !!"<<std::endl;
    std::ofstream outfile;
    buf[0]= 0xAA;
    buf[1]= 0x0B;
    buf[2]= 0xF4;
    buf[3]= 0x00;
    buf[4]= 0x00;
    buf[5]= 0x55;
    buf[6]= 0x04;
    buf[7]= 0x02;
    buf[8]= 0x00;
    buf[9]= 0x1E;
    buf[10]= 0x01;
    buf[11]= 0x02;
    buf[12]= 0x30;
    buf[13]= 0x40;
    while(1)
    {
        int i;
   size_t sum_Length =(size_t) 14 ;
   uint16_t out = crc16(sum_Length,0xFFFF,buf);
   char low_crc = out<<8;
   char high_crc = out>>8;
//   buf[14] = low_crc;
//   buf[15] = high_crc;
#if 1
   len= UART0_Send(fd,buf,14);
   usleep(2000000);
//  sleep(1);
//    std::cout<<out<<"  "<<buf<<std::endl;
  if(!len){
    std::cout<<"send data error!!! "<<std::endl;
    return 0;    
  }
  else{
    
     std::cout<<"send data successful ! "<<std::endl;
  }
#endif
#if 0
  len = UART0_Recv(fd, result_buf,20); 
std::cout<<"reading data ... "<<std::endl;
  if(!len){
    std::cout<<"receive data error!!! "<<std::endl;
    return 0;    
  }

  for(i=0; i<BUFSIZE; i++)			 
  {		

    printf("%x ",(unsigned char) result_buf[i]);	
    
  }
#endif
#if 1
        len = UART0_Recv(fd, result_buf,14);  
   usleep(2000000);
	std::cout<<"Recv buffer len :"<<len<<std::endl;
                     if(len == BUFSIZE)  
                     {  
                        if((unsigned char)result_buf[0] == 0xaa)
                        {
                          printf("receive data is :\n");
                          for(i=0;i<len;i++)
                          {
                            printf("%x ",(unsigned char)result_buf[i]);
                          }
                          printf("\n");
                          printf("len = %d\n",len);  
                          //outfile << buf;
                        //  strcpy(result_buf , buf);
                        }
                        else
                        {
			  printf("error! Processing.....\n");
                          for(i=0; i<BUFSIZE; i++)
			  {
			    if((unsigned char)result_buf[i] == 0x88)
			    {
			      
			      UART0_Recv(fd,result_buf,i);
			    }
			  }
			}
                     }
                     else if(len == 1)
		     {
		         temp_buf[0] = result_buf[0];
			 sleep(1);
			 len = UART0_Recv(fd, result_buf,BUFSIZE-1); 
			 if(len == (BUFSIZE-1))
			 {
		         for(i =0; i<(BUFSIZE-1); i++)
			 {
			   temp_buf[i+1] = result_buf[i];
			}
			
			 for(i=0;i<BUFSIZE;i++)
			{
			  printf("%x ",(unsigned char) temp_buf[i]);
			}
			printf("\n");			   
                        //outfile << temp_buf;
                         // strcpy(result_buf , temp_buf);
			}
		     }
		     		    
                     else  
                            {  
                                   printf("cannot receive data\n");  
				   error_cnt ++;
//				   if(error_cnt == 10)
//				   {
//				     UART0_Close(fd);
//				     return 0;
//				   }  
                            }  
#endif
#if 0
                    //outfile.open(string("/home/turtlebot/current_ult_data").c_str(),ios::trunc|ios::in | ios::binary);
                    outfile.open(string("/home/carl/Desktop/Project/CleanRobot/Protocol/Test/serial_func/current_ult_data").c_str(),ios::binary);
                    if(!outfile.is_open())
                    {
                      cout << "File open error!" << endl;
                    }
			 for(i=0;i<BUFSIZE;i++)
		    {
                       outfile <<hex << (unsigned char)temp_buf[i];
                     //    outfile << hex << ;
                    }
                    outfile.close();
/*
                    ifstream rfile("/home/turtlebot/current_ult_data", ios::in);
                     if(!rfile)
                    {
		        cout << "file read error!" << endl;	
                     }
                    char str[BUFSIZE];
                    rfile.getline(str,100);
                    cout << "file read success!" << endl;
			 for(i=0;i<BUFSIZE;i++)
			{
			  printf("%x ",(unsigned char) str[i]);
			}
                    rfile.close();
*/
#endif
    }

    UART0_Close(fd);
//   std::cout << "Hello, world!" << std::endl;
    return 0;
}
