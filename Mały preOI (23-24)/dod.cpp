#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> para;

const ll MAX = 2480000000000ll; //2.48 * 1000 * 1000 * 1000 * 1000;
set<ll> liczby = {9ll, 99ll, 999ll, 9999ll, 99999ll, 999999ll, 9999999ll, 99999999ll, 999999999ll, 9999999999ll, 99999999999ll, 999999999999ll, 9999999999999ll, 99999999999999ll, 999999999999999ll, 9999999999999999ll, 99999999999999999ll, 999999999999999999ll, 999999999999999999ll, 10000000000001ll, 5009950000599005ll, 10009900000990001ll, 15009850005890051ll, 20009800000890002ll, 25009750005790052ll, 30009700000790003ll, 35009650005690053ll, 40009600000690004ll, 45009550005590054ll, 50009500000590005ll, 55009450005490055ll, 60009400000490006ll, 65009350005390056ll, 70009300000390007ll, 75009250005290057ll, 80009200000290008ll, 85009150005190058ll, 90009100000190009ll, 95009050005090059ll, 100009000000900001ll, 105008950059800501ll, 110008900009800011ll, 115008850058800511ll, 120008800008800021ll, 125008750057800521ll, 130008700007800031ll, 135008650056800531ll, 140008600006800041ll, 145008550055800541ll, 150008500005800051ll, 155008450054800551ll, 160008400004800061ll, 165008350053800561ll, 170008300003800071ll, 175008250052800571ll, 180008200002800081ll, 185008150051800581ll, 190008100001800091ll, 195008050050800591ll, 200008000000800002ll, 205007950059700502ll, 210007900009700012ll, 215007850058700512ll, 220007800008700022ll, 225007750057700522ll, 230007700007700032ll, 235007650056700532ll, 240007600006700042ll, 245007550055700542ll, 250007500005700052ll, 255007450054700552ll, 260007400004700062ll, 265007350053700562ll, 270007300003700072ll, 275007250052700572ll, 280007200002700082ll, 285007150051700582ll, 290007100001700092ll, 295007050050700592ll, 300007000000700003ll, 305006950059600503ll, 310006900009600013ll, 315006850058600513ll, 320006800008600023ll, 325006750057600523ll, 330006700007600033ll, 335006650056600533ll, 340006600006600043ll, 345006550055600543ll, 350006500005600053ll, 355006450054600553ll, 360006400004600063ll, 365006350053600563ll, 370006300003600073ll, 375006250052600573ll, 380006200002600083ll, 385006150051600583ll, 390006100001600093ll, 395006050050600593ll, 400006000000600004ll, 405005950059500504ll, 410005900009500014ll, 415005850058500514ll, 420005800008500024ll, 425005750057500524ll, 430005700007500034ll, 435005650056500534ll, 440005600006500044ll, 445005550055500544ll, 450005500005500054ll, 455005450054500554ll, 460005400004500064ll, 465005350053500564ll, 470005300003500074ll, 475005250052500574ll, 480005200002500084ll, 485005150051500584ll, 490005100001500094ll, 495005050050500594ll, 500005000000500005ll, 505004950059400505ll, 510004900009400015ll, 515004850058400515ll, 520004800008400025ll, 525004750057400525ll, 530004700007400035ll, 535004650056400535ll, 540004600006400045ll, 545004550055400545ll, 550004500005400055ll, 555004450054400555ll, 560004400004400065ll, 565004350053400565ll, 570004300003400075ll, 575004250052400575ll, 580004200002400085ll, 585004150051400585ll, 590004100001400095ll, 595004050050400595ll, 600004000000400006ll, 605003950059300506ll, 610003900009300016ll, 615003850058300516ll, 620003800008300026ll, 625003750057300526ll, 630003700007300036ll, 635003650056300536ll, 640003600006300046ll, 645003550055300546ll, 650003500005300056ll, 655003450054300556ll, 660003400004300066ll, 665003350053300566ll, 670003300003300076ll, 675003250052300576ll, 680003200002300086ll, 685003150051300586ll, 690003100001300096ll, 695003050050300596ll, 700003000000300007ll, 705002950059200507ll, 710002900009200017ll, 715002850058200517ll, 720002800008200027ll, 725002750057200527ll, 730002700007200037ll, 735002650056200537ll, 740002600006200047ll, 745002550055200547ll, 750002500005200057ll, 755002450054200557ll, 760002400004200067ll, 765002350053200567ll, 770002300003200077ll, 775002250052200577ll, 780002200002200087ll, 785002150051200587ll, 790002100001200097ll, 795002050050200597ll, 800002000000200008ll, 805001950059100508ll, 810001900009100018ll, 815001850058100518ll, 820001800008100028ll, 825001750057100528ll, 830001700007100038ll, 835001650056100538ll, 840001600006100048ll, 845001550055100548ll, 850001500005100058ll, 855001450054100558ll, 860001400004100068ll, 865001350053100568ll, 870001300003100078ll, 875001250052100578ll, 880001200002100088ll, 885001150051100588ll, 890001100001100098ll, 895001050050100598ll, 900001000000100009ll, 905000950059000509ll, 910000900009000019ll, 915000850058000519ll, 920000800008000029ll, 925000750057000529ll, 930000700007000039ll, 935000650056000539ll, 940000600006000049ll, 945000550055000549ll, 950000500005000059ll, 955000450054000559ll, 960000400004000069ll, 965000350053000569ll, 970000300003000079ll, 975000250052000579ll, 980000200002000089ll, 985000150051000589ll, 990000100001000099ll, 995000050050000599ll};
char ostatni_znak = '#';
bool cos_wypisane = false;

void wypisz(ll x, char a, char b) {
	if (ostatni_znak != '#') {
		printf("%c", ostatni_znak);
	}
	if (ostatni_znak != a && !(a == '+' && ostatni_znak == '#')) {
		printf("0");
		printf("%c", a);
	}
	printf("%lld", x);
	cos_wypisane = true;
	ostatni_znak = b;
}

ll krok_1_pom(ll x, ll a, bool nieparzysta) {
	ll n = x; 
	ll wynik = x; 
	if (nieparzysta) {
		n /= a; 
	}
	while (n > 0) { 
		wynik = wynik * a + (n % a); 
		n /= a; 
	} 
	return wynik; 
}

void krok_1(ll max) {
	ll x;
	for (int i = 0; i <= 1; i++) { 
		ll j = 1; 
		while ((x = krok_1_pom(j, 10, i % 2)) < max) { 
			liczby.insert(x);
			j++; 
		} 
	}
}

ll krok_3_pom(ll x) {
	ll wynik = 0;
	while (x > 0) {
		wynik = wynik * 10 + x % 10;
		x /= 10;
	}
	return wynik; 
}

void krok_3(ll& a, ll& b, bool nie_obrocone) {
	if (abs(a) > abs(b)) {
		krok_3(b, a, false);
		return;
	}
	
	char znak_a = (a > 0 ? '+' : '-');
	a = abs(a);
	while (a > 0) {
		auto p = liczby.upper_bound(a);
		p--;
		ll x = (*p);
		
		a -= x;
		
		char znak_b;
		if (b < 0) {
			b += x;
			znak_b = '-';
		} else {
			b -= x;
			znak_b = '+';
		}
		
		if (nie_obrocone) {
			wypisz(x, znak_a, znak_b);
		} else {
			wypisz(x, znak_b, znak_a);
		}
	}
}

void krok_4(ll& a, ll& b, bool nie_obrocone) {
	if (b == 0) {
		krok_4(b, a, false);
		return;
	}
	
	char znak_b = (b > 0 ? '+' : '-');
	b = abs(b);
	while (b > 0) {
		auto p = liczby.upper_bound(b % 2 == 0 ? b / 2 : b / 2 + 1);
		p--;
		ll x = (*p);
		
		b -= x * 2;
		
		if (nie_obrocone) {
			wypisz(x, '+', znak_b);
			wypisz(x, '-', znak_b);
		} else {
			wypisz(x, znak_b, '+');
			wypisz(x, znak_b, '-');
		}
	}
}

int main() {
	ll a, b;
	scanf("%lld %lld", &a, &b);
	
	// Krok 1: wygeneruj liczby palindromiczne
	krok_1(MAX);

	// Krok 2: napraw parzystosc
	if (abs(a) % 2 != abs(b) % 2) {
		a -= 12;
		b -= 21;
		printf("12+");
		cos_wypisane = true;
	}
	
	// Krok 3: sprowadz jedna z liczb do zera
	krok_3(a, b, true);
	
	if (a == 0 && b == 0) {
		if (!cos_wypisane) {
			printf("0");
		} else if (ostatni_znak == '-') {
			printf("%c0", ostatni_znak);
		}
		return 0;
	}
	
	// Krok 4: sprowadz druga z liczb do zera
	krok_4(a, b, true);
	if (!cos_wypisane) {
		printf("0");
	} else if (ostatni_znak == '-') {
		printf("%c0", ostatni_znak);
	}
	
	return 0;
}
