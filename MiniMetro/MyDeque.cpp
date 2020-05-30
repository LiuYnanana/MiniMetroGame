#include "MyDeque.h"

MyDeque::MyDeque() {
	left_q = 2500;
	right_q = 2501;

}
MyDeque::position& MyDeque::operator [] (int i) {
	return deque[i];
}

bool MyDeque::empty() {
	if (right_q - left_q == 1) return true;
	return false;
}

int MyDeque::size() {
	return right_q - left_q - 1;
}

void MyDeque::push_back(position _p) {
	deque[right_q++] = _p;
}

void MyDeque::push_front(position _p) {
	deque[left_q--] = _p;
}

MyDeque::position MyDeque::front() {
	return deque[left_q + 1];
}
MyDeque::position MyDeque::back() {
	return deque[right_q - 1];
}

void MyDeque::clear() {
	left_q = 2500;
	right_q = 2501; 
}

int MyDeque::front_pos() {
	return left_q + 1;
}

int MyDeque::end_pos() {
	return right_q;
}