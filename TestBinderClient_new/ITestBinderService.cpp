#define LOG_TAG "ITeeveePlayerService"

#include <utils/Log.h>

#include "../TestBinderServer_new/ITestBinderService.h"

namespace android {

enum {
	TEST_ADD = IBinder::FIRST_CALL_TRANSACTION,
	TEST_ALLOCBUF,
};

class BpTestBinderService: public BpInterface<ITestBinderService> {
public:
	BpTestBinderService(const sp<IBinder>& impl) :
		BpInterface<ITestBinderService> (impl) {
	}

	int add(int a, int b) {
		
		Parcel data, reply;
		LOGI("Enter BpTestBinderService add,a = %d , b = %d", a, b);
		data.writeInterfaceToken(ITestBinderService::getInterfaceDescriptor());
		data.writeInt32(a);
		data.writeInt32(b);
		remote()->transact(TEST_ADD, data, &reply);
		int sum = reply.readInt32();
		LOGI("BpTestBinderService sum = %d", sum);
		return sum;
	}
	int allocbuf(int pipe_fd, const char* name, int bs) {
			Parcel data, reply;
		LOGI("Enter BpTestBinderService allocbuf,pipe_fd = %d , bs = %d", pipe_fd, bs);
		data.writeInterfaceToken(ITestBinderService::getInterfaceDescriptor());
		data.writeFileDescriptor(pipe_fd);
		data.writeCString(name);
		data.writeInt32(bs);
		remote()->transact(TEST_ALLOCBUF, data, &reply);
		int fd = reply.readFileDescriptor();
		LOGI("BpTestBinderService fd = %d", fd);
		 int fd2 = dup(fd);
		 LOGI("fd2 = %d", fd2);
		 perror("3dup: ");
		return fd2;
		
	}
};

IMPLEMENT_META_INTERFACE(TestBinderService, "android.test.ITestBinderService");

// ----------------------------------------------------------------------

status_t BnTestBinderService::onTransact(uint32_t code, const Parcel& data,
		Parcel* reply, uint32_t flags) {
	switch (code) {
	case TEST_ADD: {
		
		CHECK_INTERFACE(ITestBinderService, data, reply);
		int a = data.readInt32();
		int b = data.readInt32();
		LOGI("Enter BnTestBinderService add,a = %d , b = %d", a, b);
		int sum = 0;
		sum  = add(a, b);
		LOGI("BnTestBinderService sum = %d", sum);
		 reply->writeInt32(sum);
		return sum;
	}

	case TEST_ALLOCBUF: {
		
		CHECK_INTERFACE(ITestBinderService, data, reply);
		int pipe_fd = data.readFileDescriptor();
		const char *name = data.readCString();
		int bs = data.readInt32();
		
		LOGI("Enter BnTestBinderService add,pipe_fd = %d , bs = %d", pipe_fd, bs);
		int sum = 0;
		int fd  = allocbuf(pipe_fd, name, bs);
		LOGI("2BnTestBinderService fd = %d", fd);
		 reply->writeFileDescriptor(fd);
		 int fd2= dup(fd);
		  LOGI("fd2 = %d", fd2);
		 perror("2dup: ");
		return sum;
	}
	default:
		return BBinder::onTransact(code, data, reply, flags);
	}
}

}
