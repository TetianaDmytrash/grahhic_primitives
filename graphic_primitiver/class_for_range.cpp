#include "class_for_range.h"
#include <math.h>

void class_for_range::range_max_and_min_int(int* arr, int* max_value, int* min_value, int length) {
	*max_value = *min_value = arr[0];
	for (int i = 1; i < length; i++) {
		if (arr[i] < *min_value) {
			*min_value = arr[i];
		}
		else if (arr[i] > *max_value) {
			*max_value = arr[i];
		}
	}
}

void class_for_range::range_max_and_min_float(float* arr, int* max_val, int* min_val, int length) {
	float max_value, min_value;
	max_value = min_value = arr[0];
	for (int i = 1; i < length; i++) {
		if (arr[i] < min_value) {
			min_value = arr[i];
		}
		else if (arr[i] > max_value) {
			max_value = arr[i];
		}
	}
	*max_val = round(max_value);
	*min_val = round(min_value);
}

void class_for_range::move_max_min_int(int*arr, int* max_value, int* min_value, int length, int offset) {
	for (int i = 0; i < length; i++) {
		arr[i] += offset;
	}
	*max_value += offset;
	*min_value += offset;
}

void class_for_range::move_max_min_float(float* arr, int* max_value, int* min_value, int length, int offset) {
	for (int i = 0; i < length; i++) {
		arr[i] += offset;
	}
	*max_value += offset;
	*min_value += offset;
}