#include <iostream>
#include <string>
#include <cctype>

using namespace std;
/*----��Ա�ṹ��----*/
struct member{
	string m_name;      //��Ա����
	member * father;    //��ָ��
	member * child;     //��ָ��
	member * brotherPre;    //�ֵ�ָ��
	member * brotherNext;   //�ֵ�ָ��
	int sonNum;         //ֱϵ�������
};
/*----��������----*/
class familyTree{
private:
	member * ancestor;      //����  
public:
	familyTree();           //���캯�� 
	~familyTree();          //��������

	void addMember();       //��Ӽ�ͥ��Ա
	void completeMember();  //���Ƽ�ͥ
	void deleteMember();    //����ֲ���ͥ
	void changeName();      //���ļ�ͥ��Ա����
	void get();             //�鿴��Ա��Ϣ

	member * findMember(string name, member * key);  //���Ҽ�ͥ��Ա
	void showSons(member * p);   //��ʾ�Ӵ�
	void destroy(member * p);    //�ݹ�ɾ��
	member * memberCreate();     //��Ա���ɺ���
	void ancestorCreate();       //���ڵ����ɺ���
	
};

familyTree::familyTree(){
	ancestor = new member;
	ancestor->m_name = "";
	ancestor->sonNum = 0;
	ancestor->father = NULL;
	ancestor->child = NULL;
	ancestor->brotherPre = NULL;
	ancestor->brotherNext = NULL;
}

familyTree::~familyTree(){
	destroy(ancestor);
}

/*----���ӳ�Ա----*/
void familyTree::addMember(){
	string name;
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	cin >> name;
	member *p = findMember(name, ancestor);
	if (p == NULL){
		cout << "���޴���" << endl;
		return;
	}
	cout << "������" << p->m_name << "����ӵĶ��ӣ���Ů������������";
	member * newChild = memberCreate();
	newChild->father = p;
	p->sonNum++;
	cin >> newChild->m_name;
	if (!p->child){
		p->child = newChild;
		showSons(p);
		return;
	}
	member * temp = p;
	temp = temp->child;
	while (temp->brotherNext){
		temp = temp->brotherNext;
	}
	temp->brotherNext = newChild;
	showSons(p);
}

/*----���Ƽ�ͥ��Ա----*/
void familyTree::completeMember(){
	string name;
	cout << "������Ҫ������ͥ���˵�����:";
	cin >> name;
	member * p = findMember(name, ancestor);
	if (p == NULL){
		cout << "δ�ҵ�����" << endl;
		return;
	}
	if (p->child){
		cout << p->m_name << "�Ѿ���������ͥ" << endl;
		return;
	}
	cout << "������" << p->m_name << "�Ķ�Ů������";
	cin >> p->sonNum;
	if (p->sonNum == 0)
		return;
	cout << "����������" << p->m_name << "�Ķ�Ů��������";
	p->child = memberCreate();
	member *temp = p->child;
	cin >> temp->m_name;
	temp->father = p;
	for (int i = 1; i < p->sonNum; i++){
		member *brother = memberCreate();
		cin >> brother->m_name;
		brother->father = p;
		brother->brotherPre = temp;
		temp->brotherNext = brother;
		temp = temp->brotherNext;
	}
	showSons(p);
}

/*----ɾ����ͥ��Ա----*/
void familyTree::deleteMember(){
	string name;
	member *p = NULL;
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	cin >> name;
	p = findMember(name, ancestor);
	if (p == NULL){
		cout << "���޴���" << endl;
		return;
	}
	showSons(p);
	if (p->brotherPre && p->brotherNext){
		p->brotherPre->brotherNext = p->brotherNext;
		p->brotherNext->brotherPre = p->brotherPre;
		p->father->sonNum--;
	}
	if (p->brotherPre && !p->brotherNext){
		p->brotherPre->brotherNext = NULL;
		p->father->sonNum--;
	}
	if (!p->brotherPre && p->brotherNext){
		p->father->child = p->brotherNext;
		p->brotherNext->brotherPre = NULL;
		p->father->sonNum--;
	}
	if (!p->brotherPre && !p->brotherNext){
		    p->father->child = NULL;
			p->father->sonNum--;
	}
	if (p->child)
	    destroy(p->child);
	delete p;
}

/*----���¼�ͥ��Ա��Ϣ----*/
void familyTree::changeName(){
	string name;
	cout << "������Ҫ�����������˵�����:";
	cin >> name;
	member *p = findMember(name, ancestor);
	if (p == NULL){
		cout << "���޴���" << endl;
		return;
	}
	cout << "��������ĺ������:";
	cin >> p->m_name;
	cout << name << "�Ѿ�����Ϊ" << p->m_name << endl;
}

/*----���Ҽ�ͥ��Ա----*/
member * familyTree::findMember(string name, member * key){
	member * p = key, *ans = NULL, *temp = p;
	
	if (p->m_name == name)
		return p;
	while (temp->brotherNext){
		ans = findMember(name, temp->brotherNext);
		if (ans)
			return ans;
		temp = temp->brotherNext;
	}
	temp = p;
	if (temp->child)
		ans = findMember(name, temp->child);
	return ans;
}

/*----��һ��չʾ----*/
void familyTree::showSons(member * p){
	if (p->sonNum == 0){
		cout << p->m_name << "û�к��" << endl;
		return;
	}
	member * temp = p->child;
	cout << p->m_name << "�ĵ�һ��������:";
	for (int i = 0; i < p->sonNum; i++){
		cout << temp->m_name << "   ";
		if (temp->brotherNext)
			temp = temp->brotherNext;
	}
}

/*----�ͷſռ�----*/
void familyTree::destroy(member * p){
	member *temp = p;
	while (temp->brotherNext){
		temp = temp->brotherNext;
	}
	while (temp->brotherPre){
		temp = temp->brotherPre;
		temp->brotherNext->brotherPre = NULL;
		temp->brotherNext->brotherNext = NULL;
		destroy(temp->brotherNext);
	}
	if (temp->child)
		destroy(temp->child);
	delete p;
}

/*----��ȡ��ͥ��Ա----*/
void familyTree::get(){
	string name;
	cout << "������Ҫ�鿴�˵�����:";
	cin >> name;
	member * p = findMember(name, ancestor);
	if (p == NULL){
		cout << "���޴���" << endl;
		return;
	}
	cout << "������" << p->m_name << endl;
	if (p->father){
	    cout << "���ף�" << p->father->m_name << endl;
		if (p->father->sonNum > 0){
			member  *temp = p->father->child;
			cout << "�ֵܣ�";
			for (int i = 1; i < p->father->sonNum;){
				if (temp->m_name != name){
					cout << temp->m_name << "    ";
					i++;
				}
				if (temp->brotherNext)
					temp = temp->brotherNext;
			}
			cout << endl;
		}
	}
	showSons(p);
}

/*----������ͥ��Ա�ڵ�----*/
member * familyTree::memberCreate(){
	member *p = new member;
	
	p->m_name = "";
	p->sonNum = 0;
	p->father = NULL;
	p->child = NULL;
	p->brotherNext = NULL;
	p->brotherPre = NULL;

	return p;
}

/*----�������ڵ�----*/
void familyTree::ancestorCreate(){
	cout << "���Ƚ���һ�����ף�" << endl
		<< "������Ҫ������ͥ���˵�������";
	cin >> ancestor->m_name;
	cout << "�˼��׵������ǣ�" << ancestor->m_name << endl;
	cout << endl;
}

int main(){
	familyTree Family;
	char order;
	system("color 0B");
    cout << "==================================================================" << endl;
	cout << "**                         ���׹���ϵͳ                         **" << endl;
	cout << "==================================================================" << endl;
	cout << "**                                                              **" << endl;
	cout << "**                                                              **" << endl;
	cout << "**                       ��ѡ��Ҫִ�еĲ�����                   **" << endl;
	cout << "**                                                              **" << endl;
	cout << "**                   ������ͥ---------------   A                **" << endl;
	cout << "**                                                              **" << endl;
	cout << "**                   ��Ӽ�ͥ��Ա------------  B                **" << endl;
	cout << "**                                                              **" << endl;
	cout << "**                   ��ɢ�ֲ���Ա------------  C                **" << endl;
	cout << "**                                                              **" << endl;
	cout << "**                   ���ļ�ͥ��Ա��Ϣ--------- D                **" << endl;
	cout << "**                                                              **" << endl;
	cout << "**                   �鿴��Ա��Ϣ------------- E                **" << endl;
	cout << "**                                                              **" << endl;
	cout << "**                   �˳�ϵͳ----------------- F                **" << endl;
	cout << "**                                                              **" << endl;
	cout << "**                                                              **" << endl;
	cout << "==================================================================" << endl;

	Family.ancestorCreate();

	cout << "��ѡ��Ҫִ�еĲ���:";
	cin >> order;
	while (order != 'F'){
		switch (order){
		case 'A':
			Family.completeMember();
			break;
		case 'B':
			Family.addMember();
			break;
		case 'C':
			Family.deleteMember();
			break;
		case 'D':
			Family.changeName();
			break;
		case 'E':
			Family.get();
			break;
		default:
			cout << "��������";
			break;
		}
		cout << endl << endl;
		cout << "��ѡ��Ҫִ�еĲ���:";
		cin >> order;
	}
	return 0;
}
