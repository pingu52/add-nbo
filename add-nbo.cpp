/**
 * @file add-nbo.cpp
 * @author pingu52 (gudrbs9852@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-04-20
 * 32 bit 숫자가 파일에 4바이트의 크기로 저장되어 있다(network byte order). 
 * 2개의 파일로부터 숫자를 읽어 들여 그 합을 출력하는 프로그램을 작성하라.
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h> 
#include <stdint.h> 
#include <string.h>
#include <netinet/in.h> 

// 16진수를 10진수로 변환하는 함수
int hex_to_dec(uint32_t hxd){
    int decimal = 0; // 10진수로 변환한 값을 저장할 변수
    char str[10]; // 16진수를 문자열로 변환하기 위한 배열
    snprintf(str, sizeof(char)* 10, "%x", hxd); // 16진수를 문자열로 변환하여 str배열에 저장
    for (int i = 0; i<=strlen(str); i++) { // 문자열 길이만큼 반복
        if (str[i] >= 'A' && str[i] <= 'F') // A ~ F 인 경우
            decimal = decimal * 16 + str[i] - 'A' + 10; // 10진수로 변환하여 decimal에 더함
        else if (str[i] >= 'a' && str[i] <= 'f') // a ~ f 인 경우
            decimal = decimal * 16 + str[i] - 'a' + 10; 
        else if(str[i] >= '0' && str[i] <= '9')// 0 ~ 9 인 경우 
            decimal = decimal * 16 + str[i] - '0';
    }
    return decimal;
}

 int main(int argc, char* argv[]){
    // 전달된 인자의 개수 확인
    if (argc != 3){ 
        printf("인자는 2개가 필요합니다.\n");
    } else {
        // 두 파일을 읽기 모드로 열어서 파일 포인터를 fp1과 fp2에 할당.
        FILE* fp1 = fopen(argv[1], "rb");
        FILE* fp2 = fopen(argv[2], "rb");

        // fp1이나 fp2가 NULL일 경우 파일 열기 실패
        if (fp1 == NULL || fp2 == NULL) {
            printf("ERROR\n");
            return -1;
        } else {
            // 두 파일에서 각각 4바이트씩 데이터를 읽어서 uint32_t 타입의 변수에 할당
            uint32_t bin1, bin2;
            fread(&bin1, sizeof(u_int32_t), 1, fp1);
            fread(&bin2, sizeof(uint32_t), 1, fp2);

            // 네트워크 바이트 오더링을 호스트 바이트 오더링으로 변환
            bin1 = ntohl(bin1);
            bin2 = ntohl(bin2);

            // 각 데이터를 16진수와 10진수로 변환하여 출력
            printf("%d(0x%x) + ", hex_to_dec(bin1), bin1);
			printf("%d(0x%x) = ", hex_to_dec(bin2), bin2);
			printf("%d(0x%x)\n", hex_to_dec(bin1+bin2), bin1+bin2);

            fclose(fp1);
            fclose(fp2);

            return 0;
        }
    }

 }