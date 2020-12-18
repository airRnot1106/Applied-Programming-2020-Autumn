// 学生証番号:
// 氏　　　名:

#include <stdio.h>
#include <string.h>
#include <math.h>

FILE	*fp;

unsigned char	r_img[2048][2048];
unsigned char	g_img[2048][2048];
unsigned char	b_img[2048][2048];

typedef struct tagBITMAPFILEHEADER {
	unsigned short	bfType;
	unsigned int	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned int	bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	unsigned int	biSize;
	int		biWidth;
	int		biHeight;
	unsigned short	biPlanes;
	unsigned short	biBitCount;
	unsigned int	biCompression;
	unsigned int	biSizeImage;
	int		biXPixPerMeter;
	int		biYPixPerMeter;
	unsigned int	biClrUsed;
	unsigned int	biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagDATA {
    int x0;
    int y0;
    int x1;
    int y1;
    int x2;
    int y2;
    double hAxis;
    double wAxis;
    double rd;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    int thk;
} DATA;

//*** 1.塗りつぶし長方形の関数
void SolidFilledRectangle(DATA rectangle);
//*** 2.長方形の関数
void Rectangle(DATA rectangle);
//*** 3.塗りつぶし円の関数
void SolidFilledCircle(DATA cir);
//*** 4.円の関数
void Circle(DATA cir);
//*** 5-1.線分の関数 - 線幅2t+1
void LineSegment1(DATA line);
//*** 5-2.線分の関数 - 線幅2t+1画素◆
void LineSegment2(DATA line);
//*** 5-2-1.画素◆の関数
void Pixel(DATA pixel, int i, int j);
//*** 5-3.線分の関数 - 線幅2t+1画素●
void LineSegment3(DATA line);
//*** 6.三角形の関数
void Triangle(DATA tri);
//*** 7.正方形の関数
void Square(DATA square);
//*** 8.塗りつぶし楕円の関数
void SolidFilledEllipse(DATA ellipse);
//*** 9.楕円の関数
void Ellipse(DATA ellipse);

int	main(void)
{
	BITMAPFILEHEADER    file_header;
	BITMAPINFOHEADER    info_header;
	char		    file_name[80];
	int		    i, j, width, height;
    int zukei;

    DATA rectangle;
    DATA cir;
    DATA line;
    DATA tri;
    DATA square;
    DATA ellipse;

	width = 2048;	// 画像ファイルの幅の画素数
	height = 2048;	// 画像ファイルの高さの画素数

	file_header.bfType = 0x4d42;
	file_header.bfSize = width * height * 3 + 54; // ファイルサイズ
	file_header.bfReserved1 = 0;
	file_header.bfReserved2 = 0;
	file_header.bfOffBits = 54;

	info_header.biSize = 40;
	info_header.biWidth = width;   // 画像ファイルの幅の画素数
	info_header.biHeight = height; // 画像ファイルの高さ縦の画素数
	info_header.biPlanes = 1;
	info_header.biBitCount = 24;
	info_header.biCompression = 0;
	info_header.biSizeImage = 0;
	info_header.biXPixPerMeter = 3780;
	info_header.biYPixPerMeter = 3780;
	info_header.biClrUsed = 0;
	info_header.biClrImportant = 0;

	//* 以下画像ファイルを作る処理 *//

	// 画像データ用２次元配列にデータを書き込む
	for(j = 0; j < height; j++){
		for(i = 0; i < width; i++){
			r_img[i][j] = 255;
			g_img[i][j] = 255;
			b_img[i][j] = 255;
		}
	}
    j = height/2;
    for(i = 0; i < width; i++){
        r_img[i][j] = 0; // R
        g_img[i][j] = 0; // G
        b_img[i][j] = 0; // B
    }   
    i = width/2;
    for(j = 0; j < height; j++){
        r_img[i][j] = 0; // R
        g_img[i][j] = 0; // G
        b_img[i][j] = 0; // B
    }
    for(j = height%100/2; j < height; j+=100){
        for(i = 0; i < width; i+=4){
            r_img[i][j] = 0; // R
            g_img[i][j] = 0; // G
            b_img[i][j] = 0; // B
        }
    }
    for(i = width%100/2; i < width; i+=100) {
        for(j = 0; j < height; j+=4){
            r_img[i][j] = 0; // R
            g_img[i][j] = 0; // G
            b_img[i][j] = 0; // B
        }
    }
    while(1){
        printf("図形を選択>\n1:塗りつぶし長方形\n2:長方形\n3:塗りつぶし円\n4:円\n5:線分\n6:三角形\n7:正方形\n8:塗りつぶし楕円\n9:楕円\n99:終了\n");
        scanf("%d", &zukei);
        //*** 塗りつぶし長方形ここから
        if(zukei == 1){
            printf("1点目のX座標とY座標を入力: ");
            scanf("%d%d", &rectangle.x0, &rectangle.y0);
            printf("2点目のX座標とY座標を入力: ");
            scanf("%d%d", &rectangle.x1, &rectangle.y1);
            printf("色情報 r g b を入力: ");
            scanf("%hhd%hhd%hhd", &rectangle.r, &rectangle.g, &rectangle.b);
            rectangle.x0 += width / 2;
            rectangle.y0 += height / 2;
            rectangle.x1 += height / 2;
            rectangle.y1 += width / 2;
            SolidFilledRectangle(rectangle);
        }   //*** 塗りつぶし長方形ここまで
        //*** 塗りつぶしなし長方形ここから
        else if(zukei == 2){
            printf("1点目のX座標とY座標を入力: ");
            scanf("%d%d", &rectangle.x0, &rectangle.y0);
            printf("2点目のX座標とY座標を入力: ");
            scanf("%d%d", &rectangle.x1, &rectangle.y1);
            printf("太さ情報を入力: ");
            scanf("%d", &rectangle.thk);
            printf("色情報 r g b を入力: ");
            scanf("%hhd%hhd%hhd", &rectangle.r, &rectangle.g, &rectangle.b);
            rectangle.x0 += width / 2;
            rectangle.y0 += height / 2;
            rectangle.x1 += height / 2;
            rectangle.y1 += width / 2;
            Rectangle(rectangle);
        }   //*** 塗りつぶしなし長方形ここまで
        //*** 塗りつぶし円ここから
        else if(zukei == 3){
            printf("中心のX座標とY座標を入力: ");
            scanf("%d%d", &cir.x0, &cir.y0);
            printf("半径を入力: ");
            scanf("%lf", &cir.rd);
            printf("cx: %d, cy: %d, rd: %.f\n", cir.x0, cir.y0, cir.rd);
            printf("色情報 r g b を入力: ");
            scanf("%hhd%hhd%hhd", &cir.r, &cir.g, &cir.b);
            cir.x0 += width / 2;
            cir.y0 += height / 2;
            SolidFilledCircle(cir);
        }   //*** 塗りつぶし円ここまで
        //*** 円ここから
        else if(zukei == 4){
            printf("中心のX座標とY座標を入力: ");
            scanf("%d%d", &cir.x0, &cir.y0);
            printf("半径を入力: ");
            scanf("%lf", &cir.rd);
            if(cir.rd > (width / 2) + cir.x0 || cir.rd > (width / 2) - cir.x0 || cir.rd > (height / 2) + cir.y0 || cir.rd > (height / 2) - cir.y0){
                printf(">>> この中心と半径では円が描画範囲に描けません <<<\n");
            } else {
                printf("太さ情報を入力: ");
                scanf("%d", &cir.thk);
                if(cir.rd + cir.thk > (width / 2) + cir.x0 || cir.rd + cir.thk > (width / 2) - cir.x0 || cir.rd + cir.thk > (height / 2) + cir.y0 || cir.rd + cir.thk > (height / 2) - cir.y0){
                    printf(">>> この中心と半径と太さでは円が描画範囲に描けません <<<\n");
                } else {
                    printf("cx: %d, cy: %d, rd: %.f, thk: %d\n", cir.x0, cir.y0, cir.rd, cir.thk);
                    printf("色情報 r g b を入力: ");
                    scanf("%hhd%hhd%hhd", &cir.r, &cir.g, &cir.b);
                    cir.x0 += width / 2;
                    cir.y0 += height / 2;
                    Circle(cir);
                }
            }
        }   //*** 円ここまで
        //*** 線分ここから
        else if(zukei == 5){
            printf("1点目のX座標とY座標を入力: ");
            scanf("%d%d", &line.x0, &line.y0);
            printf("2点目のX座標とY座標を入力: ");
            scanf("%d%d", &line.x1, &line.y1);
            printf("太さ情報を入力: ");
            scanf("%d", &line.thk);
            printf("色情報 r g b を入力: ");
            scanf("%hhd%hhd%hhd", &line.r, &line.g, &line.b);
            line.x0 += width / 2;
            line.y0 += height / 2;
            line.x1 += height / 2;
            line.y1 += width / 2;
            LineSegment1(line);
        }   //*** 線分ここまで
        //*** 三角形ここから
        else if(zukei == 6){
            printf("1点目のX座標とY座標を入力: ");
            scanf("%d%d", &tri.x0, &tri.y0);
            printf("2点目のX座標とY座標を入力: ");
            scanf("%d%d", &tri.x1, &tri.y1);
            printf("3点目のX座標とY座標を入力: ");
            scanf("%d%d", &tri.x2, &tri.y2);
            if((tri.x0 * tri.y1) + (tri.x1 * tri.y2) + (tri.x2 * tri.y0) == (tri.y0 * tri.x1) + (tri.y1 * tri.x2) + (tri.y2 * tri.x0)){
                printf(">>> 入力した3点では三角形は描けません <<<\n");
            } else {
                printf("太さ情報を入力: ");
                scanf("%d", &tri.thk);
                printf("色情報 r g b を入力: ");
                scanf("%hhd%hhd%hhd", &tri.r, &tri.g, &tri.b);
                tri.x0 += width / 2;
                tri.y0 += height / 2;
                tri.x1 += height / 2;
                tri.y1 += width / 2;
                tri.x2 += height / 2;
                tri.y2 += width / 2;
                Triangle(tri);
            }
        }   //*** 三角形ここまで
        //*** 正方形ここから
        else if(zukei == 7){
            printf("1点目のX座標を入力: ");
            scanf("%d%d", &square.x0, &square.y0);
            printf("2点目のY座標を入力: ");
            scanf("%d%d", &square.x1, &square.y1);
            printf("太さ情報を入力: ");
            scanf("%d", &square.thk);
            printf("色情報 r g b を入力: ");
            scanf("%hhd%hhd%hhd", &square.r, &square.g, &square.b);
            square.x0 += width / 2;
            square.y0 += height / 2;
            square.x1 += width / 2;
            square.y1 += height / 2;
            Square(square);
        }   //*** 正方形ここまで
        //*** 塗りつぶし楕円ここから
        else if(zukei == 8){
            printf("中心のX座標とY座標を入力: ");
            scanf("%d%d", &ellipse.x0, &ellipse.y0);
            printf("横径を入力: ");
            scanf("%lf", &ellipse.wAxis);
            printf("縦径を入力: ");
            scanf("%lf", &ellipse.hAxis);
            printf("色情報 r g b を入力: ");
            scanf("%hhd%hhd%hhd", &ellipse.r, &ellipse.g, &ellipse.b);
            ellipse.x0 += width / 2;
            ellipse.y0 += height / 2;
            SolidFilledEllipse(ellipse);
        }   //*** 塗りつぶし楕円ここまで
        //*** 楕円ここから
        else if(zukei == 9){
            printf("中心のX座標とY座標を入力: ");
            scanf("%d%d", &ellipse.x0, &ellipse.y0);
            printf("横径を入力: ");
            scanf("%lf", &ellipse.wAxis);
            printf("縦径を入力: ");
            scanf("%lf", &ellipse.hAxis);
            if(ellipse.wAxis > (width / 2) + ellipse.x0 || ellipse.wAxis > (width / 2) - ellipse.x0 || ellipse.hAxis > (height / 2) + ellipse.y0 || ellipse.hAxis > (height / 2) - ellipse.y0){
                printf(">>> この中心と横径と縦径では円が描画範囲に描けません <<<\n");
            } else {
                printf("太さ情報を入力: ");
                scanf("%d", &ellipse.thk);
                if(ellipse.wAxis + ellipse.thk > (width / 2) + ellipse.x0 || ellipse.wAxis + ellipse.thk > (width / 2) - ellipse.x0 || ellipse.hAxis + ellipse.thk > (height / 2) + ellipse.y0 || ellipse.hAxis + ellipse.thk > (height / 2) - ellipse.y0){
                    printf(">>> この中心と横径と縦径と太さでは円が描画範囲に描けません <<<\n");
                } else {
                    printf("色情報 r g b を入力: ");
                    scanf("%hhd%hhd%hhd", &ellipse.r, &ellipse.g, &ellipse.b);
                    ellipse.x0 += width / 2;
                    ellipse.y0 += height / 2;
                    Ellipse(ellipse);
                }
            }
        }   //*** 楕円ここまで
        //*** 終了ここから
        else if(zukei == 99){
            break;
        }   //*** 終了ここまで
        //*** 該当なしここから
        else if(zukei < 1 || (zukei > 9 && zukei < 99) || zukei > 99){
            printf(">>> 該当するものがありません <<<\n");
        }   //*** 該当なしここまで
    }

	//* 画像ファイル名の設定
	//* Ｃドライブの temp というフォルダーに Zukei.bmp というファイルを作る
    /*  保存場所のパス名を"strcpy(file_name, "XXX");"のXXXに記述する
        Windowsの場合>  C:\\temp\\zukei.bmp     など
        MacOSの場合>    /Users/username/Desktop など
    */
	for (i = 0; i < 80; i++)
		file_name[i] = 0;
	strcpy(file_name, "XXX");
	printf("File Name: %s\n\n", file_name);

	fp = fopen(file_name, "wb");
	if (fp != 0)
		printf("%s OPEN!\n", file_name);
	else {
		printf("%s OPEN FAILED! ", file_name);
		perror("error");
		return -1;
	}

	//* 以下データをファイルに書き込む処理 *//

	fwrite(&file_header.bfType, sizeof(file_header.bfType), 1, fp);
	fwrite(&file_header.bfSize, sizeof(file_header.bfSize), 1, fp);
	fwrite(&file_header.bfReserved1, sizeof(file_header.bfReserved1), 1, fp);
	fwrite(&file_header.bfReserved2, sizeof(file_header.bfReserved2), 1, fp);
	fwrite(&file_header.bfOffBits, sizeof(file_header.bfOffBits), 1, fp);

	fwrite(&info_header.biSize, sizeof(info_header.biSize), 1, fp);
	fwrite(&info_header.biWidth, sizeof(info_header.biWidth), 1, fp);
	fwrite(&info_header.biHeight, sizeof(info_header.biHeight), 1, fp);
	fwrite(&info_header.biPlanes, sizeof(info_header.biPlanes), 1, fp);
	fwrite(&info_header.biBitCount, sizeof(info_header.biBitCount), 1, fp);
	fwrite(&info_header.biCompression, sizeof(info_header.biCompression), 1, fp);
	fwrite(&info_header.biSizeImage, sizeof(info_header.biSizeImage), 1, fp);
	fwrite(&info_header.biXPixPerMeter, sizeof(info_header.biXPixPerMeter), 1, fp);
	fwrite(&info_header.biYPixPerMeter, sizeof(info_header.biYPixPerMeter), 1, fp);
	fwrite(&info_header.biClrUsed, sizeof(info_header.biClrUsed), 1, fp);
	fwrite(&info_header.biClrImportant, sizeof(info_header.biClrImportant), 1, fp);

	//* 画像データをファイルに書き込む
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			fwrite(&b_img[i][j], 1, 1, fp); // B
			fwrite(&g_img[i][j], 1, 1, fp); // G
			fwrite(&r_img[i][j], 1, 1, fp); // R
		}
	}
    
	//* 以上データをファイルに書き込む処理 *//

	//* 完了の表示
	printf("%s データ書き込み完了\n", file_name);

	//* ファイルを閉じる
	fclose(fp);

	//* 以上画像ファイルを作る処理 *//

	return 0;
}
//*** 塗りつぶし長方形ここから
void SolidFilledRectangle(DATA rectangle){
    int i, j, tmp;
    if(rectangle.x0 > rectangle.x1){
        tmp = rectangle.x0;
        rectangle.x0 = rectangle.x1;
        rectangle.x1 = tmp;
    }
    if(rectangle.y0 > rectangle.y1){
        tmp = rectangle.y0;
        rectangle.y0 = rectangle.y1;
        rectangle.y1 = tmp;
    }
    for(i = rectangle.x0; i <= rectangle.x1; i++){
        for(j = rectangle.y0; j <= rectangle.y1; j++){
            r_img[i][j] = rectangle.r; // R
            g_img[i][j] = rectangle.g; // G
            b_img[i][j] = rectangle.b; // B
        }
    }
}   //*** 塗りつぶし長方形ここまで
//*** 長方形ここから
void Rectangle(DATA rectangle){
    DATA line;
    line.thk = rectangle.thk;
    line.r = rectangle.r;
    line.g = rectangle.g;
    line.b = rectangle.b;
    line.x0 = rectangle.x0;
    line.y0 = rectangle.y0;
    line.x1 = rectangle.x1;
    line.y1 = rectangle.y0;
    LineSegment2(line);
    line.x0 = rectangle.x1;
    line.y0 = rectangle.y0;
    line.x1 = rectangle.x1;
    line.y1 = rectangle.y1;
    LineSegment2(line);
    line.x0 = rectangle.x1;
    line.y0 = rectangle.y1;
    line.x1 = rectangle.x0;
    line.y1 = rectangle.y1;
    LineSegment2(line);
    line.x0 = rectangle.x0;
    line.y0 = rectangle.y1;
    line.x1 = rectangle.x0;
    line.y1 = rectangle.y0;
    LineSegment2(line);
}   //*** 長方形ここまで
//*** 塗りつぶし円ここから
void SolidFilledCircle(DATA cir){
    int i, j;
    for(i = cir.x0 - cir.rd; i <= cir.x0 + cir.rd; i++){
        for(j = cir.y0 - sqrt((cir.rd * cir.rd) - ((i - cir.x0) * (i - cir.x0))); j <= cir.y0 + sqrt((cir.rd * cir.rd) - ((i - cir.x0) * (i - cir.x0))); j++){
            r_img[i][j] = cir.r; // R
            g_img[i][j] = cir.g; // G
            b_img[i][j] = cir.b; // B
        }
    }
}   //*** 塗りつぶし円ここまで
//*** 円ここから
void Circle(DATA cir){
    int i, j;
    if(cir.thk > 0){
        for(i = cir.x0 - cir.rd - cir.thk; i <= cir.x0 - cir.rd + cir.thk; i++){
            for(j = cir.y0 - sqrt(((cir.rd + cir.thk) * (cir.rd + cir.thk)) - ((i - cir.x0) * (i - cir.x0))); j <= cir.y0 + sqrt(((cir.rd + cir.thk) * (cir.rd + cir.thk)) - ((i - cir.x0) * (i - cir.x0))); j++){
                r_img[i][j] = cir.r; // R
                g_img[i][j] = cir.g; // G
                b_img[i][j] = cir.b; // B
            }
        }
        for(i = cir.x0 + cir.rd - cir.thk; i <= cir.x0 + cir.rd + cir.thk; i++){
            for(j = cir.y0 - sqrt(((cir.rd + cir.thk) * (cir.rd + cir.thk)) - ((i - cir.x0) * (i - cir.x0))); j <= cir.y0 + sqrt(((cir.rd + cir.thk) * (cir.rd + cir.thk)) - ((i - cir.x0) * (i - cir.x0))); j++){
                r_img[i][j] = cir.r; // R
                g_img[i][j] = cir.g; // G
                b_img[i][j] = cir.b; // B
            }
        }
        for(i = cir.x0 - cir.rd + cir.thk; i <= cir.x0 + cir.rd - cir.thk; i++){
            for(j = cir.y0 + sqrt(((cir.rd - cir.thk) * (cir.rd - cir.thk)) - ((i - cir.x0) * (i - cir.x0))); j <= cir.y0 + sqrt(((cir.rd + cir.thk) * (cir.rd + cir.thk)) - ((i - cir.x0) * (i - cir.x0))); j++){
                r_img[i][j] = cir.r; // R
                g_img[i][j] = cir.g; // G
                b_img[i][j] = cir.b; // B
            }
            for(j = cir.y0 - sqrt(((cir.rd + cir.thk) * (cir.rd + cir.thk)) - ((i - cir.x0) * (i - cir.x0))); j <= cir.y0 - sqrt(((cir.rd - cir.thk) * (cir.rd - cir.thk)) - ((i - cir.x0) * (i - cir.x0))); j++){
                r_img[i][j] = cir.r; // R
                g_img[i][j] = cir.g; // G
                b_img[i][j] = cir.b; // B
            }
        }
    } else {
        for(i = cir.x0 - cir.rd; i <= cir.x0 + cir.rd; i++){
            j = cir.y0 + sqrt((cir.rd * cir.rd) - ((i - cir.x0) * (i - cir.x0)));
            r_img[i][j] = cir.r; // R
            g_img[i][j] = cir.g; // G
            b_img[i][j] = cir.b; // B
            j = cir.y0 - sqrt((cir.rd * cir.rd) - ((i - cir.x0) * (i - cir.x0)));
            r_img[i][j] = cir.r; // R
            g_img[i][j] = cir.g; // G
            b_img[i][j] = cir.b; // B
        }
        for(j = cir.y0 - cir.rd; j<= cir.y0 + cir.rd; j++){
            i = cir.x0 + sqrt((cir.rd * cir.rd) - ((j - cir.y0) * (j - cir.y0)));
            r_img[i][j] = cir.r; // R
            g_img[i][j] = cir.g; // G
            b_img[i][j] = cir.b; // B
            i = cir.x0 - sqrt((cir.rd * cir.rd) - ((j - cir.y0) * (j - cir.y0)));
            r_img[i][j] = cir.r; // R
            g_img[i][j] = cir.g; // G
            b_img[i][j] = cir.b; // B
        }
    }
}   //*** 円ここまで
//*** 線分 - 線幅2t+1ここから
void LineSegment1(DATA line){
    double dx, dy;
    int i, j;
    dx = line.x1 - line.x0;
    dy = line.y1 - line.y0;
    if(dy / dx >= -1 && dy / dx <= 1){
        if(line.x0 < line.x1){
            for(i = line.x0 - line.thk; i <= line.x1 + line.thk; i++){
                for(j = (dy / dx) * (i - line.x0) + line.y0 - line.thk; j <= (dy / dx) * (i - line.x0) + line.y0 + line.thk; j++){
                    r_img[i][j] = line.r; // R
                    g_img[i][j] = line.g; // G
                    b_img[i][j] = line.b; // B
                }
            }
        } else {
            for(i = line.x1; i <= line.x0; i++){
                for(j = (dy / dx) * (i - line.x0) + line.y0 - line.thk; j <= (dy / dx) * (i - line.x0) + line.y0 + line.thk; j++){
                    r_img[i][j] = line.r; // R
                    g_img[i][j] = line.g; // G
                    b_img[i][j] = line.b; // B
                }
            }
        }
    } else {
        if(line.y0 < line.y1){
            for(j = line.y0 - line.thk; j <= line.y1 + line.thk; j++){
                for(i = (dx / dy) * (j - line.y1) + line.x1 - line.thk; i <= (dx / dy) * (j - line.y1) + line.x1 + line.thk; i++){
                    r_img[i][j] = line.r; // R
                    g_img[i][j] = line.g; // G
                    b_img[i][j] = line.b; // B
                }
            }
        } else {
            for(j = line.y1; j <= line.y0; j++){
                for(i = (dx / dy) * (j - line.y1) + line.x1 - line.thk; i <= (dx / dy) * (j - line.y1) + line.x1 + line.thk; i++){
                    r_img[i][j] = line.r; // R
                    g_img[i][j] = line.g; // G
                    b_img[i][j] = line.b; // B
                }
            }
        }
    }
}   //*** 線分 - 線幅2t+1ここまで

//*** 線分 - 線幅2t+1画素◆ここから
void LineSegment2(DATA line){
    DATA pixel;
    double dx, dy;
    int i, j;
    pixel.thk = line.thk;
    pixel.r = line.r;
    pixel.g = line.g;
    pixel.b = line.b;
    dx = line.x1 - line.x0;
    dy = line.y1 - line.y0;
    if(dy / dx >= -1 && dy / dx <= 1){
        if(line.x0 < line.x1){
            for(i = line.x0; i <= line.x1; i++){
                j = (dy / dx) * (i - line.x0) + line.y0;
                Pixel(pixel, i, j);
            }
        } else {
            for(i = line.x1; i <= line.x0; i++){
                j = (dy / dx) * (i - line.x0) + line.y0;
                Pixel(pixel, i, j);
            }
        }
    } else {
        if(line.y0 < line.y1){
            for(j = line.y0; j <= line.y1; j++){
                i = (dx / dy) * (j - line.y1) + line.x1;
                Pixel(pixel, i, j);
            }
        } else {
            for(j = line.y1; j <= line.y0; j++){
                i = (dx / dy) * (j - line.y1) + line.x1;
                Pixel(pixel, i, j);
            }
        }
    }
}   //*** 線分 - 線幅2t+1画素◆ここまで
//*** 線分 - 線幅2t+1画素●ここから
void LineSegment3(DATA line){
    DATA pixel;
    DATA cir;
    double dx, dy;
    int i, j;
    pixel.thk = line.thk;
    pixel.r = line.r;
    pixel.g = line.g;
    pixel.b = line.b;
    cir.rd = pixel.thk;
    cir.r = pixel.r;
    cir.g = pixel.g;
    cir.b = pixel.b;
    dx = line.x1 - line.x0;
    dy = line.y1 - line.y0;
    if(dy / dx >= -1 && dy / dx <= 1){
        if(line.x0 < line.x1){
            for(i = line.x0; i <= line.x1; i++){
                j = (dy / dx) * (i - line.x0) + line.y0;
                cir.x0 = i;
                cir.y0 = j;
                SolidFilledCircle(cir);
            }
        } else {
            for(i = line.x1; i <= line.x0; i++){
                j = (dy / dx) * (i - line.x0) + line.y0;
                cir.x0 = i;
                cir.y0 = j;
                SolidFilledCircle(cir);
            }
        }
    } else {
        if(line.y0 < line.y1){
            for(j = line.y0; j <= line.y1; j++){
                i = (dx / dy) * (j - line.y1) + line.x1;
                cir.x0 = i;
                cir.y0 = j;
                SolidFilledCircle(cir);
            }
        } else {
            for(j = line.y1; j <= line.y0; j++){
                i = (dx / dy) * (j - line.y1) + line.x1;
                cir.x0 = i;
                cir.y0 = j;
                SolidFilledCircle(cir);
            }
        }
    }
}   //*** 線分 - 線幅2t+1画素●ここまで

//*** 三角形ここから
void Triangle(DATA tri){
    DATA line;
    line.thk = tri.thk;
    line.r = tri.r;
    line.g = tri.g;
    line.b = tri.b;
    line.x0 = tri.x0;
    line.y0 = tri.y0;
    line.x1 = tri.x1;
    line.y1 = tri.y1;
    LineSegment3(line);
    line.x0 = tri.x1;
    line.y0 = tri.y1;
    line.x1 = tri.x2;
    line.y1 = tri.y2;
    LineSegment3(line);
    line.x0 = tri.x2;
    line.y0 = tri.y2;
    line.x1 = tri.x0;
    line.y1 = tri.y0;
    LineSegment3(line);
}   //*** 三角形ここまで
//*** 正方形ここから
void Square(DATA square){
    DATA line;
    line.thk = square.thk;
    line.r = square.r;
    line.g = square.g;
    line.b = square.b;
    line.x0 = square.x0;
    line.y0 = square.y0;
    line.x1 = (square.x0 + square.x1) / 2 + (square.y1 - square.y0) / 2;
    line.y1 = (square.y0 + square.y1) / 2 - (square.x1 - square.x0) / 2;
    LineSegment2(line);
    line.x0 = (square.x0 + square.x1) / 2 + (square.y1 - square.y0) / 2;
    line.y0 = (square.y0 + square.y1) / 2 - (square.x1 - square.x0) / 2;
    line.x1 = square.x1;
    line.y1 = square.y1;
    LineSegment2(line);
    line.x0 = square.x1;
    line.y0 = square.y1;
    line.x1 = (square.x0 + square.x1) / 2 - (square.y1 - square.y0) / 2;
    line.y1 = (square.y0 + square.y1) / 2 + (square.x1 - square.x0) / 2;
    LineSegment2(line);
    line.x0 = (square.x0 + square.x1) / 2 - (square.y1 - square.y0) / 2;
    line.y0 = (square.y0 + square.y1) / 2 + (square.x1 - square.x0) / 2;
    line.x1 = square.x0;
    line.y1 = square.y0;
    LineSegment2(line);
}   //*** 正方形ここまで
//*** 塗りつぶし楕円ここから
void SolidFilledEllipse(DATA ellipse){
    int i, j;
    for(i = ellipse.x0 - ellipse.wAxis; i <= ellipse.x0 + ellipse.wAxis; i++){
        for(j = ellipse.y0 - (ellipse.hAxis / ellipse.wAxis) * sqrt((ellipse.wAxis * ellipse.wAxis) - ((i - ellipse.x0) * (i - ellipse.x0))); j <= ellipse.y0 + (ellipse.hAxis / ellipse.wAxis) * sqrt((ellipse.wAxis * ellipse.wAxis) - ((i - ellipse.x0) * (i - ellipse.x0))); j++){
            r_img[i][j] = ellipse.r; // R
            g_img[i][j] = ellipse.g; // G
            b_img[i][j] = ellipse.b; // B
        }
    }
}   //*** 塗りつぶし楕円ここまで
//*** 楕円ここから
void Ellipse(DATA ellipse){
    int i, j;
    if(ellipse.thk > 0){
        for(i = ellipse.x0 - ellipse.wAxis - ellipse.thk; i <= ellipse.x0 - ellipse.wAxis + ellipse.thk; i++){
            for(j = ellipse.y0 - (ellipse.hAxis / ellipse.wAxis) * sqrt(((ellipse.wAxis + ellipse.thk) * (ellipse.wAxis + ellipse.thk)) - ((i - ellipse.x0) * (i - ellipse.x0))); j <= ellipse.y0 + (ellipse.hAxis / ellipse.wAxis) * sqrt(((ellipse.wAxis + ellipse.thk) * (ellipse.wAxis + ellipse.thk)) - ((i - ellipse.x0) * (i - ellipse.x0))); j++){
                r_img[i][j] = ellipse.r; // R
                g_img[i][j] = ellipse.g; // G
                b_img[i][j] = ellipse.b; // B
            }
        }
        for(i = ellipse.x0 + ellipse.wAxis - ellipse.thk; i <= ellipse.x0 + ellipse.wAxis + ellipse.thk; i++){
            for(j = ellipse.y0 - (ellipse.hAxis / ellipse.wAxis) * sqrt(((ellipse.wAxis + ellipse.thk) * (ellipse.wAxis + ellipse.thk)) - ((i - ellipse.x0) * (i - ellipse.x0))); j <= ellipse.y0 + (ellipse.hAxis / ellipse.wAxis) * sqrt(((ellipse.wAxis + ellipse.thk) * (ellipse.wAxis + ellipse.thk)) - ((i - ellipse.x0) * (i - ellipse.x0))); j++){
                r_img[i][j] = ellipse.r; // R
                g_img[i][j] = ellipse.g; // G
                b_img[i][j] = ellipse.b; // B
            }
        }
        for(i = ellipse.x0 - ellipse.wAxis + ellipse.thk; i <= ellipse.x0 + ellipse.wAxis - ellipse.thk; i++){
            for(j = ellipse.y0 + (ellipse.hAxis / ellipse.wAxis) * sqrt(((ellipse.wAxis - ellipse.thk) * (ellipse.wAxis - ellipse.thk)) - ((i - ellipse.x0) * (i - ellipse.x0))); j <= ellipse.y0 + (ellipse.hAxis / ellipse.wAxis) * sqrt(((ellipse.wAxis + ellipse.thk) * (ellipse.wAxis + ellipse.thk)) - ((i - ellipse.x0) * (i - ellipse.x0))); j++){
                r_img[i][j] = ellipse.r; // R
                g_img[i][j] = ellipse.g; // G
                b_img[i][j] = ellipse.b; // B
            }
            for(j = ellipse.y0 - (ellipse.hAxis / ellipse.wAxis) * sqrt(((ellipse.wAxis + ellipse.thk) * (ellipse.wAxis + ellipse.thk)) - ((i - ellipse.x0) * (i - ellipse.x0))); j <= ellipse.y0 - (ellipse.hAxis / ellipse.wAxis) * sqrt(((ellipse.wAxis - ellipse.thk) * (ellipse.wAxis - ellipse.thk)) - ((i - ellipse.x0) * (i - ellipse.x0))); j++){
                r_img[i][j] = ellipse.r; // R
                g_img[i][j] = ellipse.g; // G
                b_img[i][j] = ellipse.b; // B
            }
        }
    } else {
        for(i = ellipse.x0 - ellipse.wAxis; i <= ellipse.x0 + ellipse.wAxis; i++){
            j = ellipse.y0 + (ellipse.hAxis / ellipse.wAxis) * sqrt((ellipse.wAxis * ellipse.wAxis) - ((i - ellipse.x0) * (i - ellipse.x0)));
            r_img[i][j] = ellipse.r; // R
            g_img[i][j] = ellipse.g; // G
            b_img[i][j] = ellipse.b; // B
            j = ellipse.y0 - (ellipse.hAxis / ellipse.wAxis) * sqrt((ellipse.wAxis * ellipse.wAxis) - ((i - ellipse.x0) * (i - ellipse.x0)));
            r_img[i][j] = ellipse.r; // R
            g_img[i][j] = ellipse.g; // G
            b_img[i][j] = ellipse.b; // B
        }
        for(j = ellipse.y0 - ellipse.hAxis; j<= ellipse.y0 + ellipse.hAxis; j++){
            i = ellipse.x0 + (ellipse.wAxis / ellipse.hAxis) * sqrt((ellipse.hAxis * ellipse.hAxis) - ((j - ellipse.y0) * (j - ellipse.y0)));
            r_img[i][j] = ellipse.r; // R
            g_img[i][j] = ellipse.g; // G
            b_img[i][j] = ellipse.b; // B
            i = ellipse.x0 - (ellipse.wAxis / ellipse.hAxis) * sqrt((ellipse.hAxis * ellipse.hAxis) - ((j - ellipse.y0) * (j - ellipse.y0)));
            r_img[i][j] = ellipse.r; // R
            g_img[i][j] = ellipse.g; // G
            b_img[i][j] = ellipse.b; // B
        }
    }
}   //*** 楕円ここまで
//*** 画素◆ここから
void Pixel(DATA pixel, int i, int j){
    int m, n;
    for(n = j; n <= j + pixel.thk; n++){
        for(m = i - pixel.thk + (n - j); m <= i + pixel.thk - (n - j); m++){
            r_img[m][n] = pixel.r; // R
            g_img[m][n] = pixel.g; // G
            b_img[m][n] = pixel.b; // B
        }
    }
    for(n = j - pixel.thk; n <= j; n++){
        for(m = i - pixel.thk - (n - j); m <= i + pixel.thk + (n - j); m++){
            r_img[m][n] = pixel.r; // R
            g_img[m][n] = pixel.g; // G
            b_img[m][n] = pixel.b; // B
        }
    }
}   //*** 画素◆ここまで