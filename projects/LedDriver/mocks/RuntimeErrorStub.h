#ifndef RUNTIME_ERROR_STUB_H
#define RUNTIME_ERROR_STUB_H

#ifdef __cplusplus
extern "C" {
#endif
	void RuntimeErrorStub_Reset(void);
	const char *RuntimeErrorStub_GetLastError(void);

	int RuntimeErrorStub_GetLastParameter(void);

#ifdef __cplusplus
}
#endif

#endif

