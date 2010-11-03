#include <time.h>
#include <errno.h>

/* a thread safe sleep function... */
void ssgl_sleep(int seconds)
{
	int rc;
	struct timespec req, rem;

	req.tv_sec = seconds;
	req.tv_nsec = 0;
	rem.tv_sec = 0;
	rem.tv_nsec = 0;

	do {
		rc = nanosleep(&req, &rem);
		if (rc == 0)
			break;
		if (rc < 0 && errno == -EINTR) {
			req = rem;
			rem.tv_sec = 0;
			rem.tv_nsec = 0;
			continue;
		}
	} while (1);
}

