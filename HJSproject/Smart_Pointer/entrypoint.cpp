#include <memory>

class test
{
public:
	int k;

	test() { k = 10; };
	~test() { k = 0; }
};

void foo_sh(std::shared_ptr<test> data)
{
	data.get()->k = 20;
}

void foo_uniq(std::unique_ptr<test> data)
{
	data.get()->k = 20;
}

void foo_uniq_ref(std::unique_ptr<test>& dataRef)
{
	dataRef.get()->k = 20;
}

int main()
{
	//공유(강한 참조) 스마트 포인터
	std::shared_ptr<test> sp = std::make_shared<test>();
	{
		sp->k = 100;
		foo_sh(sp);
	}

	//유일 스마트 포인터
	std::unique_ptr<test> up = std::make_unique<test>();
	{
		//foo_uniq(up);	참조가 안되서 오류
		foo_uniq_ref(up);
	}

	//약한 참조 스마트 포인터
	std::weak_ptr<test> wp;
}