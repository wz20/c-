#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>

#define MAX      100
#define NAME_LEN 10

typedef struct {
    char name[NAME_LEN];
    unsigned int score[3];
    unsigned int sum;
    unsigned int avg;
} Stu_i;

Stu_i   stu[MAX];
int     num;

//�������� 
Stu_i  input_stu(void);                    // ͨ����ʾ�����û���ȷ������һ��ѧ����¼��������������¼
void   output_stu(int i);                  // ��������������ӡ����Ӧ��ѧ����Ϣ
int    find_stu(void);                     // ͨ����ʾ�����û����Ҽ�¼������ҵ�����ʾ���ҵ��ļ�¼���������������������򷵻�-1

void   read_stu(const char *filename);     // �����ļ��������ļ��е�ѧ������
void   write_stu(const char *filename);    // ��ѧ������д�뵽ָ�����ļ���

int    confirm(const char *words);         // �����û�ȷ�ϣ�����y��Y����1������n��N����0�����������ʾ�û���������
void   safe_flush(FILE *fp);               // safe_flush(stdin)�����������룬��ֹӰ���´λ�ȡ����


void safe_flush(FILE *fp){
    int ch;
    while ( ch = fgetc(fp), ch != EOF && ch != '\n');
}

int confirm(const char *words) {
    char choice;
    puts(words);
    for (;;) {
        choice = getchar();
        safe_flush(stdin);

        switch (choice) {
        default:
            puts("����Ƿ����������룡");
            continue;
        case 'Y':
        case 'y':
            puts("��ȷ�ϣ�");
            return 1;
        case 'N':
        case 'n':
            puts("��ȡ����");
            return 0;
        }
    }
}

Stu_i input_stu(void) {
    Stu_i ret;
    puts("�����������������ġ���ѧ������ɼ����ո�ָ����ɼ�Ҫ��������:");
    while ( 4 != scanf("%s%d%d%d", ret.name,
                                  &ret.score[0],
                                  &ret.score[1],
                                  &ret.score[2])) {
        safe_flush(stdin);
        puts("������������������!");
    }
    safe_flush(stdin);
    ret.sum = ret.score[0] + ret.score[1] + ret.score[2];
    ret.avg = ret.sum/3; 
    return ret;
}

void output_stu(int i) {
    if (i < 0 || i > MAX) return;
    printf("%s\t��:%d\t��:%d\t��:%d\t�ܷ�:%d\tƽ���ɼ���%d\n",
                                stu[i].name,
                                stu[i].score[0],
                                stu[i].score[1],
                                stu[i].score[2],
                                stu[i].sum,
								stu[i].avg            );
}

int find_stu(void) {
    char name[NAME_LEN];
    int i;
    printf("������������%d���ַ�����", NAME_LEN);
    scanf("%s", name);
    safe_flush(stdin);
    for (i = 0; i < num; i++) {
        if (0 == strcmp(stu[i].name, name)) {
            output_stu(i);
            return i;
        }
    }
    puts("û���ҵ���¼!");
    return -1;
}

void read_stu(const char *filename) {
    FILE *fp = fopen(filename, "rt");
    if (NULL != fp) {
        fread(&num, sizeof(int), 1, fp);
        fread(stu, sizeof(Stu_i), num, fp);
    }
    fclose(fp);
}

void write_stu(const char* filename) {
    FILE *fp = fopen(filename, "wt");
    if (NULL != fp) {
        fwrite(&num, sizeof(int), 1, fp);
        fwrite(stu, sizeof(Stu_i), num, fp);
        fclose(fp);
        puts("����ɹ�!");
    }
    else puts("���ļ�ʧ�ܣ�");
}

int main(void) {
	//���ô��ڴ�С
	system("mode con:cols=100 lines=35");
	//���ô����������ɫ
	system("color C");
    const char *filename = "stu_info.txt";

    read_stu(filename); // ��������
    printf("************************��ӭʹ��ѧ���ɼ�����ϵͳ**************************\n"
           "                                                                          \n"
           "                                                                          \n"
		   "****************-��ǰ����%d����¼,����������%d����¼**********************\n"
		   "-------------------------205����ѧ������ϵͳ------------------------------\n",
           num, MAX);

    for (;;) {
    char choice;
    int i, j;

        printf( "                   �˵�:\n"
                " **                   1.����ѧ���ɼ�                                      **\n"
                " **                   2.¼��ѧ���ɼ�                                      **\n"
                " **                   3.ɾ��ѧ���ɼ�                                      **\n"
                " **                   4.�޸�ѧ���ɼ�                                      **\n"
                " **                   5.����ɼ���ƽ���֣�                                **\n"
                " **                   6.��ʾѧ���ɼ�                                      **\n"
                " **                   7.��        ��                                      **\n"
                " **                   0.��        ��                                      **\n"
                "  �������:");

        choice = getchar();
        safe_flush(stdin);

        switch (choice) {
        case '1': // ����
            find_stu();
            break;
        case '2': // ¼�� 
            if (num < MAX) {
                stu[num] = input_stu();
                output_stu(num);
                num++;
                puts("¼��ɹ�!");
            }
            else puts("��¼�������޷�¼�룡");
            break;
        case '3': // ɾ��
            i = find_stu();
            if (-1 != i) {
                if (confirm("ȷ��ɾ����Y OR N")) {
                    while (i++ != num) {
                        stu[i-1] = stu[i];
                    }
                    num--;
                    puts("ɾ���ɹ�!");
                }
            }
            break;
        case '4': // �޸�
            i = find_stu();
            if (-1 != i) {
                stu[i] = input_stu();
                output_stu(i);
                puts("�޸ĳɹ���");
            }
            break;
        case '5': // ����ƽ��������
            for (i = 0; i < num-1; i++)     // ð���������Ѿ��źõ�
                for (j=0; j < num-1-i; j++) // ����û�źõ�
                    if ( stu[j].avg < stu[j+1].avg ) {
                        Stu_i t = stu[j];
                        stu[j] = stu[j+1];
                        stu[j+1] = t;
                    }
            puts("����ɹ���");
            /* fall through */     // ���������Զ���ʾ
        case '6': // ��ʾ
            for (i = 0; i < num; i++) {
                printf("%4d:\t", i+1);
                output_stu(i);
            }
            break;
        case '7': // ����
            write_stu(filename);
            break;
        case '0': // �˳�
            if (confirm("�˳�ǰ���棿��Y/N��")) {
                write_stu(filename);
            }
            exit(0);
        default:
            puts("û�и���ţ�����������");
            break;
        }
    } // END for

    return 0;
}
