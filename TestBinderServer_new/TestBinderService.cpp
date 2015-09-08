#define LOG_TAG "TestBinderService"

#include <utils/Log.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cutils/ashmem.h>

#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include "binderservice.h"
#include "TestBinderService.h"


static int m_fd ;
static int m_pipe_fd;
char *m_buf;
namespace android {



void TestBinderService::instantiate() {
	LOGI("Enter TestBinderService::instantiate");
	status_t st = defaultServiceManager()->addService(
			String16("my.test.binder"), new TestBinderService());
	LOGD("ServiceManager addService ret=%d", st);
	LOGD("instantiate> end");
}

TestBinderService::TestBinderService() {
	m_fd = -1;
	m_buf = NULL;
	m_pipe_fd = -1;
	LOGD(" TestBinderServicet");
}

TestBinderService::~TestBinderService() {
	LOGD("TestBinderService destroyed,never destroy normally");
}

int TestBinderService::add(int a,int b) {
	int result = -1;
	LOGI("TestBinderService::add a = %d, b = %d.", a , b);	
	result = sum2(a, b);
	LOGI("TestBinderService::result = %d.",result);	
	return result;
}
void* TestBinderService::test_proc(void*a) {
	char buf[100];
	int len = 100;
	int read_len = -1;
	int write_len = -1;
	while(1)
	{
		read_len = read(m_pipe_fd, buf, 12);
		LOGI("TestBinderService::read_len = %d.buf = %s",read_len, buf);	
		sleep(1);
		if(read_len > 0)
		{
			//write_len = write(m_fd, "from server", 12);
			strncpy(m_buf, "from server", 12);
		}
		LOGI("TestBinderService::write_len = %d.",write_len);
	}
	
	return NULL;
}

int TestBinderService::allocbuf(int pipe_fd, const char* name, int bs) {
	int result = -1;
	pthread_t th;
	
	LOGI("TestBinderService::allocbuf pipe_fd = %d, bs = %d.", pipe_fd , bs);	
	m_pipe_fd = dup(pipe_fd);
	LOGI("m_pipe_fd = %d", m_pipe_fd);
	m_fd = ashmem_create_region(name, bs);
	if(m_fd > 0)
	{
		m_buf = (char *)mmap(0, bs, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd , 0);
		if(m_buf == (void*)-1)
			LOGI("TestBinderService mmap fail");
	}
	LOGI("TestBinderService::m_fd = %d. m_buf = 0x%x",m_fd, m_buf);	
	 int fd2 = dup(m_fd);
	 LOGI("fd2 = %d", fd2);
	 perror("1dup: ");
	pthread_create(&th, NULL, test_proc, NULL);
	return m_fd;
} 


}
