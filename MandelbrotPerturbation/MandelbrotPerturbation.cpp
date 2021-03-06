#include "pch.h"
#include "FrameCalculator.h"
#include <iostream>
#include <windows.h>

using namespace std;

string GetDocumentPath();
std::wstring s2ws(const std::string& s);

const char* xZoomPointString = "-1.25736802846652839265383159384773654166836713857126000896912753375688559878664765114255696457015368246531973104439755978333044015506759938503739206829441575363669402497147343368904702066174408250247081855416385744218741909521990441308969603994513271641284298225323509381146075334937409491188";
const char* yZoomPointString = "0.37873083102862491151257052392242106932532193327534173605649141946411779667848532042309666819671311329800095959763206221251386819369531602358854394169140220049675504811341950346171196600590463661845947574424944950533273158558278821586333530950155398785389980291835095955110139525825547062070";

int main()
{
	FrameCalculator::calculateFrame frameCalculator;

	#pragma warning(disable : 4996)

	string bufferPath = GetDocumentPath() + "\\Mandelbrot Perturbation"; //The output is in your documents folder. 
	CreateDirectory(s2ws(bufferPath).c_str(), NULL);

	frameCalculator.initializeCalculateFrame(480, 360, 1000, xZoomPointString, yZoomPointString, 2, "Sunset Gradient");
	for (int i = 0; i > -1; i++) {
		frameCalculator.calculateOneFrame(i, bufferPath.c_str());
		cout << "Frame " << i << endl;
		cin.ignore(); //Press enter to render another frame
	}
}

string GetDocumentPath()
{
	wchar_t Folder[1024];
	HRESULT hr = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, Folder);
	if (SUCCEEDED(hr))
	{
		char str[1024];
		wcstombs(str, Folder, 1023);
		return str;
	}
	else return "";
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
