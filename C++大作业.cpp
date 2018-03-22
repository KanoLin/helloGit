#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<cstdio>

/*
�����һ������Ϊ����n
������n�飬ÿ���ʽ
+��-��*��/��
����1
����2
*/

using namespace std;

struct node
{
	int data;
	node *next, *before;
	node() {
		next = before = NULL;
	}
};

//z1��z2��Ӧ�����������ֳ��ȣ�x1��x2��Ӧ����С�����ֳ��ȣ�
//zf1��zf2��Ӧ���������ţ�0��1������ zf��Ӧ��������ţ�0��1������k��Ӧ������ȣ�
int z1, z2, x1, x2, zf1, zf2, zf, k;
//s1��s2��������ʱ�洢����
string s1, s2;
//����ָ���ֱ��Ӧ����β��ͷ
//aa��bbΪ���򴢴棬ccΪ���򴢴�
node *aa, *bb, *cc, *ha, *hb, *hc;

//max()���ڱȽϴ�С
int max(int a, int b)
{
	if (a > b) return a;
	else return b;
}

//link()����������������
void link(node *&a, node *&b)
{
	b->before = a;
	a->next = b;
	a = b;
}

//build()���ڽ�����������������aa��bb
void build()
{
	zf = z1 = z2 = x1 = x2 = zf1 = zf2 = 0;
	cin >> s1;
	for (int i = 0; i < s1.size(); ++i)
	{
		if (s1[i] != ',' && s1[i] != '.' && s1[i] != '-')
		{
			node *ss = new node;
			ss->data = s1[i] - '0';
			if (aa == NULL) { ha = ss; aa = ss; }
			else link(aa,ss);
			if (!x1)z1++;
			else x1++;
		}
		else if (s1[i] == '.') x1++;
		else if (s1[i] == '-')zf1 = 1;
	}
	x1--;
	cin >> s2;
	x2 = 0;
	for (int i = 0; i < s2.size(); ++i)
	{
		if (s2[i] != ',' && s2[i] != '.'&& s2[i] != '-')
		{
			node *ss = new node;
			ss->data = s2[i] - '0';
			if (bb == NULL) { hb = ss; bb = ss; }
			else link(bb, ss);
			if (!x2)z2++;
			else x2++;
		}
		else if (s2[i] == '.') x2++;
		else if (s2[i] == '-') zf2 = 1;
	}
	x2--;
	if (x1 < 0)x1 = 0;
	if (x2 < 0)x2 = 0;
}

//patch()����С�����볤��
void patch()
{
	if (x1 > x2) 
	{
		for (int i = x2 + 1; i <= x1; ++i)
		{
			node *ss = new node;
			ss->data = 0;
			link(bb, ss);
			
		}
		x2 = x1;
	}
	else if (x1 < x2) {
		for (int i = x1 + 1; i <= x2; ++i)
		{
			node *ss = new node;
			ss->data = 0;
			link(aa, ss);
		}
		x1 = x2;
	}

}

//zeroAdd()����ĩβ����
void zeroAdd(node *&x,int t)
{
	for (int i = 1; i <= t; ++i)
	{
		node *ss = new node;
		ss->data = 0;
		link(x, ss);
	}
}

//clean()�����ͷ�����
void clean(node *p)
{
	if (p == NULL)return;
	while (p->next != NULL)
	{
		p = p->next;
		delete p->before;
		p->before = NULL;
	}
	delete p;
	p = NULL;
}

//turn()���ڷ�ת����
void turn(node *&hx, node *&xx)
{
	node *x = xx;
	node *ht, *tt;
	ht = tt = NULL;
	while (x != NULL)
	{
		node *ss = new node;
		ss->data = x->data;
		if (ht == NULL) { ht = ss; tt = ss; }
		else link(tt, ss);
		x = x->before;
	}
	clean(hx);
	hx = ht; xx = tt;
}

//errorCheck()�����жϱ������Ƿ�С��10^-6
bool errorCheck(node *p, int lenz, int lenx)
{
	if (lenz > 1 || lenx < 7)return false;
	for (int i = 1; i <= 6; ++i)
	{
		p = p->next;
		if (p->data != 0)return false;
	}
	return true;
}

//judge()�����ж���������ֵ��С��1��ʾaa��2��ʾbb��
int judge()
{
	if (z1 > z2)return 1;
	if (z1 < z2)return 2;
	node *a1 = ha, *b1 = hb;
	for (int i = 1; i <= z1 + max(x1, x2); ++i)
	{
		if (a1->data > b1->data)return 1;
		else if (a1->data < b1->data)return 2;
		a1 = a1->next; b1 = b1->next;
		if (a1 != NULL&&b1 == NULL)return 1;
		else if (a1 == NULL&&b1 != NULL)return 2;
	}
	return 1;
}


//add()�����������
void add()
{
	k = 0;
	int t = 0;
	for (int i = max(x1, x2); i > 0; --i)
	{
		k++;
		node *ss = new node;
		ss->data = aa->data + bb->data+t;
		if (ss->data >= 10) { t = 1; ss->data %= 10; }
		else t = 0;
		if (hc == NULL) {hc = ss; cc = ss;}
		else link(cc, ss);
		aa = aa->before;
		bb = bb->before;
	}
	int i = z1, j = z2;
	while (i&&j)
	{
		k++;
		node *ss = new node;
		ss->data = aa->data + bb->data + t;
		if (ss->data >= 10) { t = 1; ss->data %= 10; }
		else t = 0;
		if (hc == NULL) { hc = ss; cc = ss; }
		else link(cc, ss);
		aa = aa->before;
		bb = bb->before;
		i--; j--;
	}
	while (i == 0 && j)
	{
		k++;
		node *ss = new node;
		ss->data = bb->data + t;
		if (ss->data >= 10) { t = 1; ss->data %= 10; }
		else t = 0;
		if (hc == NULL) { hc = ss; cc = ss; }
		else link(cc, ss);
		bb = bb->before;
		j--;
	}
	while (i && j == 0)
	{
		k++;
		node *ss = new node;
		ss->data = aa->data + t;
		if (ss->data >= 10) { t = 1; ss->data %= 10; }
		else t = 0;
		if (hc == NULL) { hc = ss; cc = ss; }
		else link(cc, ss);
		aa = aa->before;
		i--;
	}
	if (t == 1) {
		k++;
		node *ss = new node;
		ss->data = 1;
		link(cc, ss);
	}//�������λ���ڽ�λ�����
}

//subtract()����������������ұ�֤����ֵ��ļ�С��
void subtract(node *aa,node *bb, int z1, int z2, int x1, int x2)
{
	k = 0;
	int t = 0;
	for (int i = max(x1, x2); i > 0; --i)
	{
		k++;
		node *ss = new node;
		ss->data = aa->data - bb->data + t;
		if (ss->data < 0) { t = -1; ss->data += 10; }
		else t = 0;
		if (hc == NULL) { hc = ss; cc = ss; }
		else link(cc, ss);
		aa = aa->before;
		bb = bb->before;
	}
	int i = z1, j = z2;
	while (i&&j)
	{
		k++;
		node *ss = new node;
		ss->data = aa->data - bb->data + t;
		if (ss->data < 0) { t = -1; ss->data += 10; }
		else t = 0;		
		if (hc == NULL) { hc = ss; cc = ss; }
		else link(cc, ss);		
		aa = aa->before;
		bb = bb->before;
		i--; j--;
	}
	while (i && j == 0)
	{
		k++;
		node *ss = new node;
		ss->data = aa->data + t;
		if (ss->data < 0) { t = -1; ss->data += 10; }
		else t = 0;
		if (hc == NULL) { hc = ss; cc = ss; }
		else link(cc, ss);
		aa = aa->before;
		i--;
	}
	if (cc->data == 0) {k--; cc = cc->before;}//�������λΪ0�����
}

//multiply()����������Чλ�����
void multiply()
{
	node *linkA=aa,*linkB=bb,*linkC,*ha0=ha,*hb0=hb;//linkA/B/C���ڳ˷�����ʱ����λ��
	int len1 = z1 + x1, len2 = z2 + x2;
	if (z1 == 0)len1++;
	if (z2 == 0)len2++;
	while (ha0->data == 0) { ha0 = ha0->next; len1--; }//ȥ��С����Чλ��ǰ��0��
	while (hb0->data == 0) { hb0 = hb0->next; len2--; }//�൱��С�������
	for (int i = 1; i <= len1 + len2; ++i)
	{
		k++;
		node *ss = new node;
		ss->data = 0;
		if (hc == NULL) { hc = ss; cc = ss; }
		else link(cc, ss);
	}
	linkC = hc;
	int t = 0,ta=len1,tb=len2;
	while (linkA != NULL&&ta>0)
	{
		cc = linkC; ta--;
		while (linkB != NULL&&tb>0)
		{
			tb--;
			cc->data += linkB->data*linkA->data;
			if (cc->data >= 10) { t = cc->data / 10; cc->data %= 10; }
			else t = 0;
			cc = cc->next;
			cc->data += t;
			linkB = linkB->before;
		}
		tb = len2;
		linkC = linkC->next;
		linkA = linkA->before;
		linkB = bb;
	}
	if (cc->data == 0) {k--; cc = cc->before;}
	if (k <= x1 + x2)
	{
		int tt = k;
		for (int i = k + 1; i <= x1 + x2+1 ;++i)
		{
			node *ss = new node;
			ss->data = 0;
			link(cc, ss);
			++tt;
		}
		k = tt;
	}
}

//divide()���ڳ���
void divide()
{
	while (ha->data == 0) { ha = ha->next; delete ha->before; ha->before = NULL; z1--; }//ȥ��С����Чλ��ǰ��0��
	while (hb->data == 0) { hb = hb->next; delete hb->before; hb->before = NULL; z2--; }
	z1 += x1; z2 += x2; x1 = x2 = 0;
	zeroAdd(aa, 11);
	z1 += 11;
	int i = z1 - z2, kd = 0;
	node *hd = NULL, *dd = NULL;
	z2 = z1;
	zeroAdd(bb, i);
	i++;
	while (i)
	{
		node *ss = new node;
		ss->data = 0;		
		while (judge() == 1&&ha->data!=0)
		{
			k = 0; hc = cc = NULL;
			subtract(aa, bb, z1, z2, x1, x2);
			turn(hc, cc);clean(ha);ha = hc; aa = cc;
			z1 = k;
			++ss->data;
		}
		if (hd == NULL) { hd = ss; dd = ss; }
		else link(dd, ss);
		kd++;
		z2--;
		bb = bb->before;
		if (bb == NULL)break;
		delete bb->next;
		bb->next = NULL;
		--i;
	}
	if (dd->data >= 5)
	{
		dd->before->data++;
		node *p = dd;
		int t = 0;
		while (p!=NULL)
		{
			p->data += t;
			if (p->data >= 10) { p->data %= 10; t = 1; }
			else t = 0;
			p = p->before;
		}
		if (t) {
			node *ss = new node;
			ss->data = 1;
			p->before = ss;
			ss->next = p;
			hd = ss;
			kd++;
		}
	}
	dd = dd->before; 
	delete dd->next; 
	dd->next = NULL;
	kd--;
	turn(hd, dd);
	if (kd <= 10)
	{
		for (int i = kd + 1; i <= 11; ++i)
		{
			node *ss = new node;
			ss->data = 0;
			link(dd, ss);
		}
		kd = 11;
		x1 = x2 = 10;
	}
	else
	{
		int t = kd;
		for (int i = t; i >= 12; --i)
		{
			if (dd->data == 0)
			{
				dd = dd->before;
				delete dd->next;
				dd->next = NULL;
				kd--;
			}
			else break;
		}
	}
	k = kd;hc = hd; cc = dd;x1 = x2 = 10;
}

//output()�������
void output()
{
	if (k == 0) return;
	int k2 = 1;
	if (zf)cout << '-';
	int t = 1;
	while (hc->data == 0 && k2 <= max(x1, x2))//�˴�Ϊȷ��С��ĩβ����0�����
	{
		k2++;
		hc = hc->next;
	}
	for (int i = k; i >= k2; i--)
	{
		if (t && i == max(x1, x2)) { cout << '.'; t = 0; }
		cout << cc->data;
		if (i>k2)cc = cc->before;
		if ((i - max(x1, x2)) % 3 == 1 && i>max(x1, x2) && i - max(x1, x2) > 3)cout << ',';
	}
	cout << endl;
}

int main()
{
	int t;
	cin >> t;
	for (int i = 1; i <= t; ++i)
	{
		char s;
		cin >> s;
		ha = hb = hc = aa = bb = cc = NULL;
		k = 0;
		build();
		int jud = judge(); //jud����������С�жϽ��
		zf = 0;
		switch (s)//�жϼӼ����������ȴ����������
		{
		case '+': {
			patch();
			if (zf1 + zf2 == 0) { add(); break; }
			if (zf1 + zf2 == 2) { add(); zf = 1; break; }
			if (zf1 == 1 && jud == 1) { zf = 1; subtract(aa, bb, z1, z2, x1, x2); break; }
			if (zf1 == 1 && jud == 2) { zf = 0; subtract(bb, aa, z2, z1, x2, x1); break; }
			if (zf2 == 1 && jud == 1) { zf = 0; subtract(aa, bb, z1, z2, x1, x2); break; }
			if (zf2 == 1 && jud == 2) { zf = 1; subtract(bb, aa, z2, z1, x2, x1); break; }
		}break;
		case '-': {
			patch();
			if (zf1 == 0 && zf2 == 1) { add(); break; }
			if (zf1 == 1 && zf2 == 0) { add(); zf = 1; break; }
			if (zf1 + zf2 == 0 && jud == 2) zf = 1;
			else if (zf1 + zf2 == 2 && jud == 1)zf = 1;
			if (jud == 1)subtract(aa, bb, z1, z2, x1, x2);
			else subtract(bb, aa, z2, z1, x2, x1);
		}break;
		case '*': {
			if (zf1 + zf2 == 1)zf = 1;
			else zf = 0;
			multiply();
			x1 = x2 = x1 + x2;
		}break;
		case '/': {
			if (errorCheck(hb, z2, x2)) { k = 0; cout << "ERROR" << endl; break; }
			patch();
			if (zf1 + zf2 == 1)zf = 1;
			else zf = 0;
			divide();
		}break;
		}
		output();
		clean(ha);
		clean(hb);
		clean(hc);
	}
	system("pause");
	return 0;
}