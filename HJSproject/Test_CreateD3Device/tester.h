#pragma once
#include "mywindow.h"
#include "mydxdevice.h"

class TestCase : public MyWindow
{
public:
	BOOL run() override;

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};