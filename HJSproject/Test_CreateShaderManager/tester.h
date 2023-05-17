#pragma once
#include "mygamecore.h"

class TestCase : public MyGameCore
{
public:
	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};