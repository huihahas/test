#define LOG_TAG "TestBinserService"

#include <unistd.h>
#include <sys/mman.h>
#include <cutils/ashmem.h>
#include <utils/Log.h>
#include <nativehelper/jni.h>
#include <nativehelper/JNIHelp.h>
#include <android_runtime/AndroidRuntime.h>
#include <binder/IServiceManager.h>
#include "../TestBinderServer_new/ITestBinderService.h"
//#include	"testBinder.h"

#include "TestBinderService.h"

using namespace android;


int write_pipe_fd = -1;
int m_fd = -1;
char *m_buf = NULL;
static void* test_proc(void*a) {
	char buf[100];
	int len = 100;
	int read_len = -1;
	int write_len = -1;
	while(1)
	{
		write_len = write(write_pipe_fd, "from client", 12);
		
		LOGI("TestBinderClient::write_len = %d.",write_len);	
		sleep(1);
		if(write_len > 0)
		{
			
		}
		if(m_buf != (void*)-1)
			LOGI("TestBinderClient::read_len = %d.m_buf = %s",read_len, m_buf);
	}
	
	return NULL;
}
extern "C" int call_send2(int callid, const char*isig, const char*osig, __va_list va)
 {
	int sum = 0;
	char *pIn;
	char*pOut;
	pthread_t th;	
	sp<ITestBinderService> mTestBinserService;
	if (mTestBinserService.get() == 0) {
		sp<IServiceManager> sm = defaultServiceManager();
		sp<IBinder> binder;
		do {
			binder = sm->getService(String16("my.test.binder"));
			if (binder != 0)
				break;
				LOGI("getService fail");
			usleep(500000); // 0.5 s
		} while (true);
		mTestBinserService = interface_cast<ITestBinderService> (binder);
		LOGE_IF(mTestBinserService == 0, "no ITestBinserService!?");
	}
	
	sum = mTestBinserService->add(3, 4);
	int pipe_fd[2];
	pipe(pipe_fd);
	write_pipe_fd = pipe_fd[1];
	LOGI("pipe_fd[0] = %d, pipe_fd[1] = %d", pipe_fd[0], pipe_fd[1]);
	 m_fd = mTestBinserService->allocbuf(pipe_fd[0], "test", 1024);
	 close(pipe_fd[0]);
	 LOGI("m_fd = %d", m_fd);
	 m_fd = dup(m_fd);
	 perror("dup: ");
	 LOGI("m_fd = %d", m_fd);
	m_buf = (char *)mmap(0, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd , 0);
	if(m_buf == (void*)-1){
			LOGI("TestBinderService mmap fail");
			perror("mmap: ");}
	 LOGI("m_fd = %d m_buf = 0x%x", m_fd, m_buf);
	pthread_create(&th, NULL, test_proc, NULL);
	close(pipe_fd[0]);
	while(1)
		sleep(1);
	
	return 0;

}


