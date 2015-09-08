#ifndef ANDROID_TESTBINDERSERVICE_H_
#define ANDROID_TESTBINDERSERVICE_H_

#include <utils/KeyedVector.h>
#include "ITestBinderService.h"

namespace android {

class TestBinderService: public BnTestBinderService {
public:
	static void instantiate();
	int add(int a,int b);
	int allocbuf(int pipe_fd, const char* name, int bs);
	static void* test_proc(void*a);

	
private:
	TestBinderService();
	virtual ~TestBinderService();
};

}

#endif /* ANDROID_TESTBINDERSERVICE_H_ */
