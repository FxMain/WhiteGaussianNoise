#include <QCoreApplication>
#include <QDebug>
#include <QFile>
void GaussionNoise(double *noise, double pSig, double fSNR, long num_of_scan);
#define nl 5000
QFile f("test.txt");
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"hello world!"<<endl;
    double noise[nl];
    double pSig=2;
    double fSNR=0.8;
    long num_of_scan=nl;
    GaussionNoise(noise, pSig,  fSNR,  num_of_scan);


    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open failed." << endl;
        return -1;
    }
    QTextStream txtOutput(&f);
    for(int i=0;i<num_of_scan;i++)
    {

        qDebug()  << noise[i];
        txtOutput << noise[i]<< endl;
    }

    f.close();
    return a.exec();
}
///////////////////////产生高斯白噪声模块///////////////
void GaussionNoise(double *noise, double pSig, double fSNR, long num_of_scan)
{
    //noise:产生的噪声数据；
    //stddeviation:噪声的标准差；
    //fSNR：信噪比；
    //pSig：信号功率；
    double pNoise, stddeviation;
    int i, j, numofvar;
    double gauvar, uDx, uEx, ranvar[100], sum, tempE, tempD;
    double mean;  //初始化变量；
    mean=0;
    uEx=1.0/2.0;
    uDx=1.0/12.0;
    numofvar=20;
    tempE=numofvar*uEx;
    tempD=sqrt(numofvar*uDx);
    pNoise=pSig/pow(10, fSNR/10);
    stddeviation=sqrt(6.88*0.00000000001);//计算噪声标准差
    for  (j=0;j<num_of_scan;j++)
    {
        sum=0;
        for  (i=0;i<numofvar;i++)
        {
            //产生均匀分布的数据；
            ranvar[i]=rand()/(1.0*RAND_MAX);
            sum=sum+ranvar[i];
        }
        //生成高斯分布的数据；
        gauvar=(sum-tempE)/tempD;
        *(noise+j)=float(gauvar*stddeviation+mean);
    }
}
