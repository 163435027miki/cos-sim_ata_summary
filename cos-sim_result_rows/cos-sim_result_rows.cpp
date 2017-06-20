#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //�����X�g���[��
#include<math.h>
#include<time.h>//���Ԃ�p����
#include <direct.h>//�t�H���_���쐬��
#include<stdio.h>
#include <windows.h>
#include <vector>

#define PI 3.14159265

using namespace std;
char date_directory[128];
FILE *fp_Angle,*fp_threshold2;	//���̓t�@�C��
FILE *fp_Angle_Summary,*fp_threshold2_Summary;	//�o�̓t�@�C��
//if((fp_arctan=fopen(math_name1,"w"))==NULL){cout<<"���̓G���[ arctan.csv���J���܂���";exit(1);//
int timeset(char date_directory[]);

int main(){
	int rows=256;	//�s	
	int cols=256;	//��
	int read_rows_stard=120;	//1����X�^�[�g
	int read_rows_goal=125;
	int sd;
	int i,j,k,l;
	int count_rows=0,count_cols=0;
	string str_Angle,str_threshold2;

	int filename_head[3]={3,10,100};
	char filename_headchar[3]="k";
	char simulation_name[128]="simulation17-0613";
	char inputfile_directry1[128];
	char inputfile_directry2[128];
	char outputfile_directry1[128];
	char outputfile_directry2[128];

	int lengh_inputfile_directry1;
	int lengh_inputfile_directry2;


	timeset(date_directory);

	//�z��̓��I�m��
	std::vector<std::vector<double>>Angle;
	std::vector<std::vector<double>>threshold2;
	Angle.resize(rows+1);
	threshold2.resize(rows+1);
	for(i=0;i<=rows;++i){
		Angle[i].resize(cols+1);
		threshold2[i].resize(cols+1);
	}

	sprintf(outputfile_directry1,"%sAngle_Summary.csv",date_directory);
	sprintf(outputfile_directry2,"%sthresholds_Summary.csv",date_directory);

	if((fp_Angle_Summary=fopen(outputfile_directry1,"w"))==NULL){cout<<"���̓G���[ Angle_Summary.csv���J���܂���";exit(1);}
	if((fp_threshold2_Summary=fopen(outputfile_directry2,"w"))==NULL){cout<<"���̓G���[ threshold2_Summary.csv���J���܂���";exit(1);}

	for(j=0;j<3;++j){
		for(i=0;i<6;++i){

			count_cols=0;
			sd=i*10;
			sprintf(inputfile_directry1,"..\\input_data\\%s\\%d%s_cossim_sd%d\\Angle.csv",simulation_name,filename_head[j],filename_headchar,sd);
			sprintf(inputfile_directry2,"..\\input_data\\%s\\%d%s_cossim_sd%d\\threshold2.csv",simulation_name,filename_head[j],filename_headchar,sd);

			lengh_inputfile_directry1=strlen(inputfile_directry1);
			lengh_inputfile_directry2=strlen(inputfile_directry2);
			

			//���̓t�@�C�����J��
			ifstream Angle_stream(inputfile_directry1);
			ifstream threshold2_stream(inputfile_directry2);
			if(!Angle_stream){cout<<"���̓G���[ Angle.csv������܂���";return 1;}
			if(!threshold2_stream){cout<<"���̓G���[ threshold2.csv������܂���";return 1;}

			//Angle��threshold��S�ēǂݍ���
			while(getline(Angle_stream,str_Angle)){

				count_rows=0;	//������

///////////////////��`//////////////////////////////////////////////////////////////
				string token_Angle;
				istringstream stream_Angle(str_Angle);
				
				getline(threshold2_stream,str_threshold2);	
				string token_threshold2;
				istringstream stream_threshold2(str_threshold2);
				
				while(getline(stream_Angle,token_Angle,',')){
					double tmp_Angle=stof(token_Angle);//�����𐔎��ɕϊ�
					Angle[count_rows][count_cols]=tmp_Angle;

					
					getline(stream_threshold2,token_threshold2,',');	
					double tmp_threshold2=stof(token_threshold2);//�����𐔎��ɕϊ�
					//printf("����");
					threshold2[count_rows][count_cols]=tmp_threshold2;
					
					++count_rows;

////////////////////break�������L��//////////////////////////////////////////////////////////////////////////////////////////////////////////
					if(count_rows==rows){
						count_cols++;
						break;
					}
				}
			}
			
			
			
			
			for(k=0;k<cols;++k){
				
				if(k>=read_rows_stard-1 && k<read_rows_goal){
					
					fprintf(fp_Angle_Summary,"%d%s_cossim_sd%d_%d,",filename_head[j],filename_headchar,sd,k+1);
					fprintf(fp_threshold2_Summary,"%d%s_cossim_sd%d_%d,",filename_head[j],filename_headchar,sd,k+1);
					
					for(l=0;l<rows;++l){
						fprintf(fp_Angle_Summary,"%f,",Angle[l][k]);
						fprintf(fp_threshold2_Summary,"%f,",threshold2[l][k]);
						//printf("����");
						if(l==rows-1){
							fprintf(fp_Angle_Summary,"\n");
							fprintf(fp_threshold2_Summary,"\n");
						}
					}
				}


			}

			//fclose(fp_Angle);
			//fclose(fp_threshold2);
			//memset�֐��ŏ�����
			memset( inputfile_directry1 , '\0' , lengh_inputfile_directry1 );
			memset( inputfile_directry2 , '\0' , lengh_inputfile_directry2 );
		}
	}
	
	fclose(fp_Angle_Summary);
	fclose(fp_threshold2_Summary);
}