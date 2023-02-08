//ovo je program koji racuna decimale broja Pi
//autor je Andrija Koncani, profesor Matematike i Fizike
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

void test ( int * );
void ispis( vector <int>  & );
void arctg( vector <int> &, int, int, int  );
void oduzimanje( vector <int> &, vector <int> &);
void mnozenje( vector <int> &, int );
int br_clanova( int, int );
void zbrajanje( vector <int> &, vector <int> &);
void ispis2 ( vector <int>  &  , vector <int>  &  );

int main()
{
	vector <int> suma01; //suma prvog clana
	vector <int> suma02; //suma drugog clana
	vector <int> suma03; //suma treceg clana
	vector <int> suma01ctrl; //suma prvog kontrolnog clana
	vector <int> suma02ctrl; //suma drugog kontrolnog clana
	vector <int> suma03ctrl; //suma treceg kontrolnog clana
	int dp, br_cl1, br_cl2, br_cl3, br_cl1_1;
    
	cout<<"Unesi broj zeljenih decimalnih mjesta:\n";
	cin>>dp;
    
	//racunanje broja potrebnih clanova 	
	br_cl1=br_clanova( 8, dp);
	br_cl1_1=br_clanova( 18, dp);
	br_cl2=br_clanova( 57, dp);
	br_cl3=br_clanova( 239, dp);
    
	arctg( suma01, 8, dp,  br_cl1 );
	arctg( suma02, 57, dp,  br_cl2 );
	arctg( suma03, 239, dp,  br_cl3 );
	mnozenje( suma01, 24);
	mnozenje( suma02, 8);
	mnozenje( suma03, 4);
	zbrajanje( suma01, suma02);
	zbrajanje( suma02, suma03);
//	ispis ( suma03 );
    
	arctg( suma01ctrl, 18, dp,  br_cl1_1 );
	arctg( suma02ctrl, 57, dp,  br_cl2 );
	arctg( suma03ctrl, 239, dp,  br_cl3 );
	mnozenje( suma01ctrl, 48);
	mnozenje( suma02ctrl, 32);
	mnozenje( suma03ctrl, 20);
	zbrajanje( suma01ctrl, suma02ctrl);
	oduzimanje( suma02ctrl, suma03ctrl);
//	ispis ( suma03ctrl );
    
	ispis2 ( suma03, suma03ctrl );
	
	return 0;
}

//funkcija koja racuna razvoj arkus tangensa
void arctg( vector <int> &suma, int b, int dp, int br_cl )
{

	int a, c, d, n1=2, e, i, l=0, y;
	vector <int> vect00; //inicijalni vektor
	vector <int> vect01; //vektor nastao daljnjim dijeljenjem inicijalnog vektora
	vector <int> vect02; //vektor nastao dijeljenjem vect01 s eksponentom
	vector <int> suma01plus; //suma pozitivnih sumanada prvog clana
	vector <int> suma01minus(dp+1, 0); ; //suma negativnih sumanada prvog clana
	
	//puni inicijalni vektor
	a=1;
	c=a;
	while (l<dp+1){
		d=c/b;
		vect00.push_back(d);
		e=c-d*b;
		c=e*10;
		l++;
	}
	suma01plus=vect00;
    
	//dijeli dalje vektor vect00 koji postaje vect01
	while ( n1<br_cl ){
		y=0;
		d=0;
		for ( int x: vect00 ){
			y=(y-d*b)*10+x;		
			d=y/b;
			vect01.push_back(d);
		}
		vect00.swap(vect01); //vect00 postaje vect01 za daljnje proracune
		vect01.clear();
		if ( n1%4==1 ){ //bira pozitivni clan
			y=0;        
			d=0;
			for ( int x: vect00 ){//dijeli sumand eksponentom n1, nastaje vect02
				y=(y-d*n1)*10+x;		
				d=y/n1;
				vect02.push_back(d);
			}
			//sumira sumu pozitivnih cl. s novonastalim clanom
			for ( i=dp; i>=0; i--){// 
				suma01plus[i]=suma01plus[i]+vect02[i];
				test( &suma01plus[i] );//prenosenje jedinice
			}
			vect02.clear();
		}
		else if ( n1%4==3 ){ //bira negativni clan
			y=0;
			d=0;
			for ( int x: vect00 ){//dijeli sumand eksponentom n1, nastaje vect02
				y=(y-d*n1)*10+x;		
				d=y/n1;
				vect02.push_back(d);
			}
			//sumira sumu negativnih cl. s novonastalim clanom
			for ( i=dp; i>=0; i--){// 
				suma01minus[i]=suma01minus[i]+vect02[i];
				test( &suma01minus[i] );
			}
			vect02.clear();
		}
		n1++;	     
	}
	oduzimanje( suma01plus, suma01minus);
	suma=suma01minus;
}

//prenosi jedinicu pri zbrajanju (ako je ima)
void test ( int *a ){
	if ( *a>9 ){
		*a=*a-10;
		*(a-1)=*(a-1)+1;
		test( a-1 );
	}
}

//ispis vektora
void ispis( vector <int>  &suma ){
	int i=0;
	for ( int x: suma){
		if ( i==0 ){
			cout<<x<<".\n";
		}
		else{
			cout<<x;
			if ( (i%10)==0 )
				cout<<" ";
			if ( (i%50)==0 )
				cout<<"\n";
			if ( (i%250)==0 )
				cout<<"\n";
		}
		i++;
	}
	cout<<"\n\n";
}

//komparativni ispis (ispis broja Pi)
void ispis2( vector <int>  &suma1,  vector <int>  &suma2 ){
	int i=0;
    
	while ( suma1[i]==suma2[i] && suma1[i+1]==suma2[i+1] ){
		if ( i==0 ){
			cout<<suma1[i]<<".\n";
		}
		else{
			cout<<suma1[i];
			if ( (i%10)==0 )
				cout<<" ";
			if ( (i%50)==0 )
				cout<<"\n";
			if ( (i%250)==0 )
				cout<<"\n";
		}
		i++;
	}
	cout<<"\n\n";
}

//oduzima vektore
void oduzimanje( vector <int> &f1, vector <int> &f0 ){
	int i=f1.size()-1;
    
	while ( i>=0 ){
		if ( f0[i]>f1[i] ){
			f1[i]=f1[i]+10;
			f0[i-1]=f0[i-1]+1;
		}
		f0[i]=f1[i]-f0[i];
		i--;
	}
}

//zbraja vektore
void zbrajanje( vector <int> &f1, vector <int> &f0 ){
	int i=f1.size()-1;
    
	while ( i>=0 ){
		f0[i]=f1[i]+f0[i];
		if ( f0[i]>9 ){
			f0[i-1]=f0[i-1]+1;
		}
		f0[i]=f0[i]%10;
		i--;
	}
}

//mnozi vektor brojem
void mnozenje( vector <int> &f1, int n ){
	int i=f1.size()-1;
	int a, b, c=0, c2=0;
    
	while ( i>=0 ){
		a=f1[i]*n;
		b=a%10;
		f1[i]=b+c+c2;
		if ( f1[i]>9 ){
			c2=f1[i]/10;
			f1[i]=f1[i]%10;
			if ( f1[i]>9 ){
				f1[i]=f1[i]%10;
			}
		}
		else
			c2=0;
		c=0;
		b=a/10;
		if ( (b=a/10)!=0 ){
			c=b;
		}
		i--;
	}
}

//racuna broj potrebnih clanova
int br_clanova( int a, int dp){
	double c=0, lg=0, n=1;
    
	while ( (dp-c)>0 ){
		lg=log10(a)+lg;
		c=lg+log10(n);  
		n++;
	}
    
	return (n+(log10(n*9/2)));
}
