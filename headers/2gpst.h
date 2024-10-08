#ifndef _2GPST_H_
#define _2GPST_H_

/* -------------------------------------------------------------------------- */
/// @brief 将世界协调时转换为GPS周内秒
/// @param y 年
/// @param m 月
/// @param d 日
/// @param h 时
/// @param min 分
/// @param sec 秒
/// @return 返回GPS周内秒
/* -------------------------------------------------------------------------- */
double Time2GPSsec(int y, int m, int d, double h, int min, double sec)
{
	if (m > 2)
	{
		y = y;
		m = m;
	}
	if (m <= 2)
	{
		y = y - 1;
		m = m + 12;
	}	
	h = h + min/60.0 + sec/3600.0;
	double JD = (int)(365.25 * y) + (int)(30.6001 * (m + 1)) + d + h/24.0 + 1720981.5;
	double MJD = JD - 2400000.5; 
	int gpsweek = (int)((MJD - 44244) / 7);
	double secofweek = (MJD - 44244.0 - gpsweek * 7.0) * 86400.0;
	return secofweek;
}

#endif