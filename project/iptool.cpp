#include "../iptools/core.h"
#include <string.h>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	image src, tgt;
	FILE *fp;
	char str[MAXLEN];
	char infile[MAXLEN];
	char outfile[MAXLEN];
    char *pch, *pch2, *pch3, *pch4, *pch5, *pch6, *pch7, *pch8, *pch9, *pch10;
    int i = 0, ROI = 0;
	
	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	while(fgets(str,MAXLEN,fp) != NULL) {
		if (strncmp(str,"#",1)==0) continue;
		int NumParameters = 0;
		
		pch = strtok(str, " ");
		strcpy(infile, pch);

		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		pch = strtok(NULL, " ");
		if (strncmp(pch,"opencv",6)==0) {
			cv::Mat I = cv::imread(infile);
			cv::Mat I2;
            cv::Mat temp;
			
			if( I.empty()) {
				cout << "Could not open or find the image: " << infile << endl;
				return -1;
			}
			
			pch = strtok(NULL, " ");
			if (strncmp(pch,"gray",4)==0) {
				utility::cv_gray(I, I2);
                cv::imwrite(outfile, I2);
			}
			else if (strncmp(pch,"blur_avg",8)==0) {
				pch = strtok(NULL, " ");
				utility::cv_avgblur(I, I2, atoi(pch));
                cv::imwrite(outfile, I2);
			}
            else if (strncmp(pch,"histStretch",11)==0) {
                pch = strtok(NULL, " ");
                ROI = atoi(pch);
                pch2 = strtok(NULL, " ");
                pch3 = strtok(NULL, " ");
                pch4 = strtok(NULL, " ");
                pch5 = strtok(NULL, " ");
                pch6 = strtok(NULL, " ");
                pch7 = strtok(NULL, " ");
                utility::histStretch(I, I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5),atoi(pch6),atoi(pch7));
                while (i < ROI-1)
                {
                    temp = I2;
                    pch2 = strtok(NULL, " ");
                    pch3 = strtok(NULL, " ");
                    pch4 = strtok(NULL, " ");
                    pch5 = strtok(NULL, " ");
                    pch6 = strtok(NULL, " ");
                    pch7 = strtok(NULL, " ");
                    utility::histStretch(temp,I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5),atoi(pch6),atoi(pch7));
                    i++;
                }
                i = 0;
                cv::imwrite(outfile, I2);
            }
            
            else if (strncmp(pch,"histEqual",9)==0) {
                pch = strtok(NULL, " ");
                ROI = atoi(pch);
                pch2 = strtok(NULL, " ");
                pch3 = strtok(NULL, " ");
                pch4 = strtok(NULL, " ");
                pch5 = strtok(NULL, " ");
                utility::histEqual(I, I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5));
                while (i < ROI-1)
                {
                    temp = I2;
                    pch2 = strtok(NULL, " ");
                    pch3 = strtok(NULL, " ");
                    pch4 = strtok(NULL, " ");
                    pch5 = strtok(NULL, " ");
                    utility::histEqual(temp,I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5));
                    i++;
                }
                i = 0;
                cv::imwrite(outfile, I2);
            }
            
            else if (strncmp(pch,"sobel",5)==0) {
                pch = strtok(NULL, " ");
                ROI = atoi(pch);
                pch2 = strtok(NULL, " ");
                pch3 = strtok(NULL, " ");
                pch4 = strtok(NULL, " ");
                pch5 = strtok(NULL, " ");
                utility::sobel(I, I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5));
                while (i < ROI-1)
                {
                    temp = I2;
                    pch2 = strtok(NULL, " ");
                    pch3 = strtok(NULL, " ");
                    pch4 = strtok(NULL, " ");
                    pch5 = strtok(NULL, " ");
                    utility::sobel(temp,I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5));
                    i++;
                }
                i = 0;
                cv::imwrite(outfile, I2);
            }
            
            else if (strncmp(pch,"canny",10)==0) {
                pch = strtok(NULL, " ");
                ROI = atoi(pch);
                pch2 = strtok(NULL, " ");
                pch3 = strtok(NULL, " ");
                pch4 = strtok(NULL, " ");
                pch5 = strtok(NULL, " ");
                pch6 = strtok(NULL, " ");
                pch7 = strtok(NULL, " ");
                utility::canny(I, I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5),atoi(pch6),atoi(pch7));
                while (i < ROI-1)
                {
                    temp = I2;
                    pch2 = strtok(NULL, " ");
                    pch3 = strtok(NULL, " ");
                    pch4 = strtok(NULL, " ");
                    pch5 = strtok(NULL, " ");
                    pch6 = strtok(NULL, " ");
                    pch7 = strtok(NULL, " ");
                    utility::canny(temp,I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5),atoi(pch6),atoi(pch7));
                    i++;
                }
                i = 0;
                cv::imwrite(outfile, I2);
            }
            
            else if (strncmp(pch,"combineCanny",12)==0) {
                pch = strtok(NULL, " ");
                ROI = atoi(pch);
                pch2 = strtok(NULL, " ");
                pch3 = strtok(NULL, " ");
                pch4 = strtok(NULL, " ");
                pch5 = strtok(NULL, " ");
                pch6 = strtok(NULL, " ");
                pch7 = strtok(NULL, " ");
                utility::combineCanny(I, I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5),atoi(pch6),atoi(pch7));
                while (i < ROI-1)
                {
                    temp = I2;
                    pch2 = strtok(NULL, " ");
                    pch3 = strtok(NULL, " ");
                    pch4 = strtok(NULL, " ");
                    pch5 = strtok(NULL, " ");
                    pch6 = strtok(NULL, " ");
                    pch7 = strtok(NULL, " ");
                    utility::combineCanny(temp,I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5),atoi(pch6),atoi(pch7));
                    i++;
                }
                i = 0;
                cv::imwrite(outfile, I2);
            }
            
            else if (strncmp(pch,"combineSobel",12)==0) {
                pch = strtok(NULL, " ");
                ROI = atoi(pch);
                pch2 = strtok(NULL, " ");
                pch3 = strtok(NULL, " ");
                pch4 = strtok(NULL, " ");
                pch5 = strtok(NULL, " ");
                utility::combineSobel(I, I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5));
                while (i < ROI-1)
                {
                    temp = I2;
                    pch2 = strtok(NULL, " ");
                    pch3 = strtok(NULL, " ");
                    pch4 = strtok(NULL, " ");
                    pch5 = strtok(NULL, " ");
                    utility::combineSobel(temp,I2,atoi(pch2),atoi(pch3),atoi(pch4),atoi(pch5));
                    i++;
                }
                i = 0;
                cv::imwrite(outfile, I2);
            }
            
            else if (strncmp(pch,"qr",2)==0) {
                pch = strtok(NULL, " ");
                utility::qr(I, I2);
            }
			else {
				printf("No function: %s\n", pch);
				continue;
			}
			
			//cv::imwrite(outfile, I2);
		}
		else {
			src.read(infile);
			if (strncmp(pch,"add",3)==0) {
				pch = strtok(NULL, " ");
				utility::addGrey(src,tgt,atoi(pch));
			}

			else if (strncmp(pch,"binarize",8)==0) {
				pch = strtok(NULL, " ");
				utility::binarize(src,tgt,atoi(pch));
			}

			else if (strncmp(pch,"scale",5)==0) {
				pch = strtok(NULL, " ");
				utility::scale(src,tgt,atof(pch));
			}

			else {
				printf("No function: %s\n", pch);
				continue;
			}
			
			tgt.save(outfile);
		}
	}
	fclose(fp);
	return 0;
}

