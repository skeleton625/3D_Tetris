#pragma once

class glLight {
private:
	float light_pos[3] = { 10, 25, -10 };
	float light_ambi[4] = { 0.4, 0.4, 0.4, 1.0 };
	float light_diff[4] = { 0.2, 0.2, 0.2, 1.0 };
	float light_spec[4] = { 0.1, 0.1, 0.1 ,1.0 };
	float light_emi[4] = { 1.0, 1.0, 1.0, 1.0 };
	float emi_format[4] = { 0.0, 0.0, 0.0, 1.0 };
public:
	void glLight_init();
	void glLight_setSunLight();
	void glLight_setObjectLight(float ambi[4], float diff[4], float spec[4]);
	void glLight_setObjectEmi();
	void glLight_setEmiFormat();
};