#pragma once
#include "mywindow.h"

class DxManager
{
public:
	vector<IDXGIAdapter*>		vAdapterList;

public:
	~DxManager();

	BOOL		getAdapterList(vector<IDXGIAdapter*>& vAdapterList);
};