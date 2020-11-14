#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int kombinacije[32][5] = {{1,2,3,4,5},
                            {1,2,3,4},{1,2,3,5},{1,2,4,5},{1,3,4,5},{2,3,4,5},
                            {1,2,3},{1,2,4},{1,3,4},{2,3,4},{1,2,5},{1,3,5},{2,3,5},{1,4,5},{2,4,5},{3,4,5},
                            {1,2},{1,3},{1,4},{1,5},{2,3},{2,4},{2,5},{3,4},{3,5},{4,5},
                            {1},{2},{3},{4},{5},
                            {}
                        }; // sve moguce kombinacije koje kockice mogu da se zardze

double KOEF_silazna = 0.06;
double KOEF_sloboda = 0.02;
double KOEF_uzlazna = 0.05;
double KOEF_najava = 0.07;


void baci(int *kocke,int n){
    int  i;
    for(i=0;i<n;i++){
        kocke[i] = rand()%6+1;
    }
} // bacanje kockica

void print(int *kockice,int n){
    int  i;
    for(i=0;i<n;i++){
        printf("%d ",kockice[i]);
    }
    putchar('\n');
} // ispis kockica

void init_list(int listic[][5],int dozvoljeno[][5]){
    int i,j;
    for(i=0;i<13;i++){
        for(j=0;j<5;j++){
            listic[i][j] = -1;
            dozvoljeno[i][j] = 0;
        }
    }
    dozvoljeno[0][0] = 1;
    dozvoljeno[12][2] = 1;
    for(i=0;i<13;i++) dozvoljeno[i][1] = dozvoljeno[i][3] = 1;
} // inicijalizacija listica i dozvoljnih pozicija na pocetku


double max_koef(double koeficijenti[][15][5],int x,int *pi,int *pj,int dozvoljeno[][5]){
    double max = 0.0;
    int i,j;
    for(i=0;i<15;i++){
        for(j=0;j<5;j++){
            if(dozvoljeno[i][j] && koeficijenti[x][i][j]>=max) max = koeficijenti[x][i][j],*pi = i, *pj = j;
        }
    }
    //printf("max = %0.2f\n",max);
    return max;
} // nalazenje maksimalnog koeficijenta

int kockice_inRange(int *kockice,int p,int k){
    int i,x,ok=1;
    for(i=p;i<=k;i++){
        if(ok == 0) return 0;
        else ok = 0;
        for(x=0;x<5;x++) if(kockice[x] == i) {ok = 1; break;}
    }
    return ok;
} // za kentu provera da li su kockice u dozvoljenom opsegu 1..5 i 2..6


int kockice_inRange2(int *kockice, int p, int k){
    int i,br=0;
    int map[6] = {0};
    for(i=0;i<5;i++) map[kockice[i]-1] ++;
    for(i=p-1;i<k;i++) if(map[i]>0) br++;
    return br;
} // za kentu provera koliko kockica je u dozvoljenom opsegu 1..5 i 2..6

int max(int a, int b){
    return (a>b)?a:b;
}

void calc_koef(double koeficijenti[][15][5],int x,int *kockice,int listic[][5],int dozvoljeno[][5],int t){
    int i,j,k;
    int map[6]={0,0,0,0,0,0};
    int identif=1,ok1,ok2;
    double broji = 0.0;
    for(i=0;i<15;i++){
        for(j=0;j<5;j++){
            if(dozvoljeno[i][j]){
                switch(i){
                    case 0:
                        for(k=0;k<5;k++) if(kockice[k] == i+1) koeficijenti[x][i][j]+= 1.0006/3;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }
                    break;

                    case 1:
                        for(k=0;k<5;k++) if(kockice[k] == i+1) koeficijenti[x][i][j]+= 1.0005/3;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }
                    break;

                    case 2:
                        for(k=0;k<5;k++) if(kockice[k] == i+1) koeficijenti[x][i][j]+= 1.0004/3;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }
                    break;


                    case 3:
                        for(k=0;k<5;k++) if(kockice[k] == i+1) koeficijenti[x][i][j]+= 1.0003/3;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }
                    break;

                    case 4:
                        for(k=0;k<5;k++) if(kockice[k] == i+1) koeficijenti[x][i][j]+= 1.0002/3;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }
                    break;

                    case 5:
                        for(k=0;k<5;k++) if(kockice[k] == i+1) koeficijenti[x][i][j]+= 1.0001/3;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }
                    break;

                    case 6:
                        broji = 0.0;
                        for(k=0;k<5;k++) broji += 1.0*kockice[k]/30;
                        if(broji > 20.0/30) koeficijenti[x][i][j] += broji;
                        //koeficijenti[x][i][j] += (broji);
                        //for(k=0;k<5;k++) koeficijenti[x][i][j]+=1.0*kockice[k]/30;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }
                    break;

                    case 7:
                        broji = 0.0;
                        for(k=0;k<5;k++) broji += 1.0*(7-kockice[k]);
                        if(broji >20.0) koeficijenti[x][i][j] += broji/30;
                        //koeficijenti[x][i][j] += (broji);
                        //for(k=0;k<5;k++) if(kockice[k]) koeficijenti[x][i][j]+= 1.0*(7-kockice[k])/30;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }
                    break;

                    case 8:
                        /*for(k=0;k<6;k++) map[k]=0;
                        for(k=0;k<5;k++) map[kockice[k]-1] ++;
                        for(k=0;k<6;k++) if(map[k]>=1)  koeficijenti[x][i][j] += 1.0/5;
                        //if(map[0]>map[5]) koeficijenti[x][i][j] += 1.0/5;
                        //else if (map[0]<map[5])koeficijenti[x][i][j] += 1.0/5;*/
                        if(kockice_inRange(kockice,1,5) || kockice_inRange(kockice,2,6))
                            koeficijenti[x][i][j] += 1.00;
                        else koeficijenti[x][i][j] += max(kockice_inRange2(kockice,1,5),kockice_inRange2(kockice,2,6))/5;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }
                    break;

                    case 9:
                        for(k=0;k<6;k++) map[k]=0;
                        for(k=0;k<5;k++) map[kockice[k]-1] ++;
                        //for(k=0;k<6;k++) if(map[k]>=3)  koeficijenti[x][i][j] += 1.0;
                        for(k=0;k<6;k++) if(map[k]>=3 && k!=0 && k!=1 && k!=2)  koeficijenti[x][i][j] += 1.0;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }

                    break;

                    case 10:
                        for(k=0;k<6;k++) map[k]=0;
                        for(k=0;k<5;k++) map[kockice[k]-1] ++;
                        ok1 = ok2 = 0;
                        for(k=0;k<6;k++) if(map[k]==3)  ok1 = 1;
                        for(k=0;k<6;k++) if(map[k]==2)  ok2 = 1;
                        if(ok1 && ok2) koeficijenti[x][i][j] += 2.4;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }

                    break;

                    case 11:
                        for(k=0;k<6;k++) map[k]=0;
                        for(k=0;k<5;k++) map[kockice[k]-1] ++;
                        for(k=0;k<6;k++) if(map[k]>=4)  koeficijenti[x][i][j] += 2.5;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }

                    break;

                    case 12:
                        for(k=0;k<6;k++) map[k]=0;
                        for(k=0;k<5;k++) map[kockice[k]-1] ++;
                        for(k=0;k<6;k++) if(map[k]>=5)  koeficijenti[x][i][j] += 2.7;
                        switch(j){
                            case 0: koeficijenti[x][i][j] += KOEF_silazna; break;
                            case 1: koeficijenti[x][i][j] += KOEF_sloboda; break;
                            case 2: koeficijenti[x][i][j] += KOEF_uzlazna; break;
                            case 3: koeficijenti[x][i][j] += KOEF_najava; break;
                        }

                    break;

                }
            }
        }
    }
} // funkcija koja racuna koeficijente za dobijenu kombinaciju kockica

void print_koef(double koeficijenti[][15][5]){
    int z,i,j;
    for(z=0;z<32;z++,printf("\n\n\n"))
        for(i=0;i<15;i++,printf("\n"))
            for(j=0;j<5;j++)
                printf("%.6f   ",koeficijenti[z][i][j]);

} // ispis za neke koef kao provera (ne koristi se)


int best_turn(int *kockice,int listic[][5],int dozvoljeno[][5],int *pi,int *pj, int t, int *turn){
    int i,j,z,sol[5], p_kockice[5],pom;
    double max_k=0.0;
    for(j=0;j<5;j++) sol[j] = 0;

    //postavi koeficijente
    double koeficijenti[32][15][5];
    for(z=0;z<32;z++)
        for(i=0;i<15;i++){
            for(j=0;j<5;j++){
                if(dozvoljeno[i][j]){
                    koeficijenti[z][i][j] = 0.0;
                }else koeficijenti[z][i][j] = -9999999.0;
            }
        }

    for(i=0;kockice[i] && i<5;i++);
    pom = 5-i;
    int pomocni[5];
    baci(pomocni,pom);
    for(i=0;i<pom;i++) kockice[4-i] = pomocni[i];

    int vrti = 1000,provera=0;
    while(vrti--){
        for(i=0;i<5;i++) p_kockice[i] = kockice[i];
        for(z=0;z<32;z++){
            pom=0;

            for(i=0;kombinacije[z][i] && i<5;i++){
                p_kockice[i] = kockice[kombinacije[z][i]-1];
            }
            pom = 5-i;
            baci(pomocni,pom);
            for(i=0;i<pom;i++) p_kockice[4-i] = pomocni[i];

            provera++;

            calc_koef(koeficijenti,z,p_kockice,listic,dozvoljeno,t);
        }
    }

    for(z=0;z<32;z++)
        for(i=0;i<15;i++)
            for(j=0;j<5;j++)
                 koeficijenti[z][i][j] *= 0.001;

    int max_z=0,pimax=-1,pjmax=-1;
    for(z=0;z<32;z++)
        if(max_koef(koeficijenti,z,pi,pj,dozvoljeno)>=max_k){
            max_k = max_koef(koeficijenti,z,pi,pj,dozvoljeno);
            max_z = z;
            pimax = *pi;
            pjmax = *pj;

        }


    for(j=0;j<4;j++)
        if(koeficijenti[max_z][8][j]>=1.0){
            if(*turn == 3){
                *turn = t;
            }
        }
    *pi = pimax;
    *pj = pjmax;
    return max_z;
} // funkcija koja igra najbolji potez i vraca redni broj kombinacije kockica koje trebaju da se zadrze za taj, u tom trenutku najbolji potez

void fill_listic(int *kockice,int listic[][5],int dozvoljeno[][5],int pi,int pj,int turn){
    int i=pi,j=pj,brojac,brojac2,ok1,ok2,k;
    int map[6]={0,0,0,0,0,0};
    if(dozvoljeno[i][j]){
        listic[i][j] = 0;
        switch(i){
            case 0:
                for(k=0;k<5;k++) if(kockice[k] == i+1) listic[i][j] += i+1;
            break;

            case 1:
                for(k=0;k<5;k++) if(kockice[k] == i+1) listic[i][j] += i+1;
            break;

            case 2:
                for(k=0;k<5;k++) if(kockice[k] == i+1) listic[i][j] += i+1;
            break;


            case 3:
                for(k=0;k<5;k++) if(kockice[k] == i+1) listic[i][j] += i+1;
            break;

            case 4:
                for(k=0;k<5;k++) if(kockice[k] == i+1) listic[i][j] += i+1;
            break;

            case 5:
                for(k=0;k<5;k++) if(kockice[k] == i+1) listic[i][j] += i+1;
            break;

            case 6:
                for(k=0;k<5;k++) listic[i][j] += kockice[k];
            break;

            case 7:
                for(k=0;k<5;k++) listic[i][j] += kockice[k];
            break;

            case 8:
                if(kockice_inRange(kockice,1,5) || kockice_inRange(kockice,2,6))
                    listic[i][j] = 46+turn*10;
                else listic[i][j] = 0;
            break;

            case 9:
                for(k=0;k<6;k++) map[k]=0;
                for(k=0;k<5;k++) map[kockice[k]-1] ++;
                for(k=0;k<6;k++) if(map[k]>=3)  listic[i][j] = 3*(k+1)+30;
            break;

            case 10:
                for(k=0;k<6;k++) map[k]=0;
                for(k=0;k<5;k++) map[kockice[k]-1] ++;
                ok1 = ok2 = 0;
                for(k=0;k<6;k++) if(map[k]==3){  ok1 = 1; brojac = 3*(k+1);}
                for(k=0;k<6;k++) if(map[k]==2){  ok2 = 1; brojac2 = 2*(k+1);}
                if(ok1 && ok2) listic[i][j] = brojac+brojac2+30;

            break;

            case 11:
                for(k=0;k<6;k++) map[k]=0;
                for(k=0;k<5;k++) map[kockice[k]-1] ++;
                for(k=5;k>=0;k--) if(map[k]>=4) { listic[i][j] = map[k]*(k+1)+40; break; }
            break;

            case 12:
                for(k=0;k<6;k++) map[k]=0;
                for(k=0;k<5;k++)  map[kockice[k]-1] ++;
                for(k=5;k>=0;k--) if(map[k]>=5)  {listic[i][j] = map[k]*(k+1)+50; break; }
            break;

        }
    }
} // ispunjavanje listica s onim sto smo dobili na kraju


void update_listic(int *kockice,int listic[][5],int dozvoljeno[][5],int turn){
    int z,i,j;
    double koeficijenti[32][15][5];
    for(z=0;z<32;z++)
        for(i=0;i<15;i++){
            for(j=0;j<5;j++){
                if(dozvoljeno[i][j]){
                    koeficijenti[z][i][j] = 0.0;
                }else koeficijenti[z][i][j] = -9999999.0;
            }
        }


    calc_koef(koeficijenti,0,kockice,listic,dozvoljeno,0);
    //calc_koef_precisely(koeficijenti,0,kockice,listic,dozvoljeno,0);
    //putchar('a');
    int max_z=0,pimax=-1,pjmax=-1,pi,pj;
    double max_k = 0.0;
    for(z=0;z<32;z++)
        if(max_koef(koeficijenti,z,&pi,&pj,dozvoljeno)>=max_k){
            //putchar('c');
            max_k = max_koef(koeficijenti,z,&pi,&pj,dozvoljeno);
            max_z = z;
            pimax = pi;
            pjmax = pj;
            //printf("max k= %.6f i= %d   j= %d max z = %d\n",max_k,pi,pj,max_z); <-----------------------------------------------
            //printf("max k= %.6f max z = %d\n",max_k,max_z);

        }

    fill_listic(kockice,listic,dozvoljeno,pimax,pjmax,turn);
} // funkcija koja arzurira listic nakon bacanja

void printL(int listic[][5],int dozvoljeno[][5]){
    int i,j,pi,pj,x;
    for(i=0;i<13;i++){
        for(j=0;j<4;j++){
            printf("%d. |%d %d     ",i,listic[i][j],dozvoljeno[i][j]);
        }
        putchar('\n');
    }
} // stampanje listica

int turns(int listic[][5]){
    int i,j,cnt=0;
    for(i=0;i<13;i++){
        for(j=0;j<4;j++){
            if(listic[i][j] == -1) cnt ++;
        }
    }
    return cnt;
} // broj poteza to kraja partije

int poeni(int listic[][5]){
    int i,j,pom[5]={0},rez=0;
    for(i=0;i<6;i++){
        for(j=0;j<4;j++){
            pom[j] += listic[i][j];
        }
    }
    for(j=0;j<4;j++){
        if(pom[j] >= 60) pom[j] += 30;
        //printf("k%d. %d \n",j,pom[j]);
        rez += pom[j];
    }
    for(j=0;j<4;j++){
        rez += (listic[6][j]-listic[7][j])*listic[0][j];
        //printf("min/max: %d. %d \n",j,(listic[6][j]-listic[7][j])*listic[0][j]);
    }
    for(i=8;i<13;i++){
        for(j=0;j<4;j++){
            rez += listic[i][j];
        }
    }
    return rez;
} // racunanje poena na kraju

void set_dozvoljeno(int dozvoljeno[][5],int listic[][5]){
    int i,j,ok1,ok2;
    for(i=0;i<13;i++){
        for(j=1;j<4;j+=2){
            dozvoljeno[i][j] = 1;
            if(listic[i][j] != -1) dozvoljeno[i][j] = 0;
        }
        for(j=0;j<4;j+=2){
            dozvoljeno[i][j] = 0;
        }
    }

    for(i=0;listic[i][0]!=-1 && i<=12;i++){
        dozvoljeno[i][0] = 0;
    }
    if(i<=12){
        dozvoljeno[i][0] = 1;
    }

    for(i=12;listic[i][2]!=-1 && i>=0;i--){
        dozvoljeno[i][2] = 0;
    }
    if(i>=0){
        dozvoljeno[i][2] = 1;
    }
} // postavljanje tj arzuriranje dozvoljenih polja nakoh svakog poteza

void igra(int *kockice,int listic[][5],int dozvoljeno[][5],int pi,int pj){
    printf("=====================================================%d =====================================================\n",turns(listic));
    baci(kockice,5);
    print(kockice,5);
    int t=3;
    int i,j,x;
    if(dozvoljeno[8][0] || dozvoljeno[8][2] || dozvoljeno[12][2]){ // mesta na kojima se stvaraju cepovi (jamb, kenta)

        //if(dozvoljeno[8][0]) listic[8][0] = 0;
        //if(dozvoljeno[8][2]) listic[8][2] = 0;
        //if(dozvoljeno[0][0]|| dozvoljeno[0][1]|| dozvoljeno[0][2]|| dozvoljeno[0][3]|| dozvoljeno[0][4]|| dozvoljeno[0][5]) KOEF_silazna = 0.40;
        //if(dozvoljeno[0][0]) KOEF_silazna = 0.08;
        //if(dozvoljeno[0][0] || dozvoljeno[0][1] || dozvoljeno[0][2] || dozvoljeno[0][3] || dozvoljeno[0][4] || dozvoljeno[0][5]) KOEF_silazna = 0.08;
        if(dozvoljeno[8][0]) KOEF_silazna = 0.80;
        if(dozvoljeno[8][2]) KOEF_uzlazna = 0.80;
        if(dozvoljeno[12][2]) KOEF_uzlazna = 0.80;
    }else{
        KOEF_silazna = 0.06;
        KOEF_uzlazna = 0.05;
    }
    int turn=3;
    while(t--){
        printf("================T = %d================\n",3-t);
        x = best_turn(kockice,listic, dozvoljeno,&pi,&pj,t,&turn);
        printf("pi=%d pj=%d\n",pi,pj);
        int sol[5]={0};
        if(pj == 3 && t == 2){
            for(i=0;i<15;i++)
                for(j=0;j<5;j++)
                    dozvoljeno[i][j] = 0;
            dozvoljeno[pi][pj] = 1;
        }else if(t == 2)
            for(i=0;i<15;i++)
                dozvoljeno[i][3] = 0;
        if(t==2 || t==1){
            for(i=0;kombinacije[x][i] && i<5;i++) sol[i] = kockice[kombinacije[x][i]-1];
            for(j=0;j<5;j++) kockice[j] = sol[j];
            printL(listic,dozvoljeno);
        }else {
            if(turn == 3) turn = 0;
            update_listic(kockice,listic,dozvoljeno,turn);
            set_dozvoljeno(dozvoljeno,listic);
            printL(listic,dozvoljeno);
            //printf("\n\n\n");
        }
        print(kockice,5);
    }
} // igranje jedne partije


int main(){
    int listic[16][5];
    int soma14[1000]={0},cnt_soma14 = 0;
    int soma13[1000]={0},cnt_soma13 = 0;
    int soma12[1000]={0},cnt_soma12 = 0;
    int soma11[1000]={0},cnt_soma11 = 0;
    int soma10[1000]={0},cnt_soma10 = 0;
    int soma09[1000]={0},cnt_soma09 = 0;
    int soma08[1000]={0},cnt_soma08 = 0;
    int soma07[1000]={0},cnt_soma07 = 0;
    int prosek = 0;
    srand(time(NULL));
    int dozvoljeno[16][5];
    init_list(listic,dozvoljeno);
    int i,j,pi,pj,x;
    //printL(listic,dozvoljeno);
    srand(time(NULL));
    //int kockice[5] = {1 ,1, 1, 1, 1},sol[5];
    int kockice[5];
    //printf("%d \n",turns(listic));
    int n=1;
    int mini=3000, maxi = 0;
    while(n--)
    {
        init_list(listic,dozvoljeno);
        //listic[12][2] = 0;
        set_dozvoljeno(dozvoljeno,listic);
        while(turns(listic))
        {
            igra(kockice,listic,dozvoljeno,pi,pj);
        }
        int pomocna_p = poeni(listic);
        printf("Rezultat: %d\n", pomocna_p);
        if(pomocna_p>maxi) maxi = pomocna_p;
        if(pomocna_p<mini) mini = pomocna_p;
        if(pomocna_p>1400) soma14[cnt_soma14++] = pomocna_p;
        else if(pomocna_p>1300) soma13[cnt_soma13++] = pomocna_p;
        else if(pomocna_p>1200) soma12[cnt_soma12++] = pomocna_p;
        else if(pomocna_p>1100) soma11[cnt_soma11++] = pomocna_p;
        else if(pomocna_p>1000) soma10[cnt_soma10++] = pomocna_p;
        else if(pomocna_p>900) soma09[cnt_soma09++] = pomocna_p;
        else if(pomocna_p>800) soma08[cnt_soma08++] = pomocna_p;
        else soma07[cnt_soma07++] = pomocna_p;

        if(pomocna_p>1200) printf("%d Rezultat: %d\n",cnt_soma10, pomocna_p);
        prosek += poeni(listic);
    }
    printf("prosek: %d\n",prosek);
    printf("Veliki skorovi: \n");

    printf("Preko 1400: \n");
    for(i=0;i<cnt_soma14;i++) printf("%d ",soma14[i]);
    printf("\n ukupno: %d\n",cnt_soma14);
    printf("Preko 1300: \n");
    for(i=0;i<cnt_soma13;i++) printf("%d ",soma13[i]);
    printf("\n ukupno: %d\n",cnt_soma13);
    printf("Preko 1200: \n");
    for(i=0;i<cnt_soma12;i++) printf("%d ",soma12[i]);
    printf("\n ukupno: %d\n",cnt_soma12);
    printf("Preko 1100: \n");
    for(i=0;i<cnt_soma11;i++) printf("%d ",soma11[i]);
    printf("\n ukupno: %d\n",cnt_soma11);
    printf("Preko 1000: \n");
    for(i=0;i<cnt_soma10;i++) printf("%d ",soma10[i]);
    printf("\n ukupno: %d\n",cnt_soma10);
    printf("Preko 900: \n");
    for(i=0;i<cnt_soma09;i++) printf("%d ",soma09[i]);
    printf("\n ukupno: %d\n",cnt_soma09);
    printf("Preko 800: \n");
    for(i=0;i<cnt_soma08;i++) printf("%d ",soma08[i]);
    printf("\n ukupno: %d\n",cnt_soma08);
    printf("Ispod 800: \n");
    for(i=0;i<cnt_soma07;i++) printf("%d ",soma07[i]);
    printf("\n ukupno: %d\n",cnt_soma07);
    printf("\nmin = %d , max = %d ",mini,maxi);
    return 0;
}
