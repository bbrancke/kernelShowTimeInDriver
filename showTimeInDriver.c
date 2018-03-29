
// gives sched_clock()
#include <linux/sched.h>
// do_div() [complicated use!]
#include <asm-generic/div64.h>

static unsigned long long nsToMs(unsigned long long dur)
{
	unsigned long long dur_ms;
	unsigned long long rem;

	dur_ms = dur;
	rem = do_div(dur_ms, 1000000);
	if (rem > 500000)
	{
		dur_ms++;
	}
	return dur_ms;
}

static void showTimeSpent(const char *who, unsigned long long start)
{
	unsigned long long end;
	unsigned long long dur;
	unsigned long long dur_ms;

	end = sched_clock();
	dur = end - start;
	dur_ms = nsToMs(dur);
	printk("%s: %llu ns (%llu ms).\n", who, dur, dur_ms);
}

// TO USE:
// someFunct(blah...) {
//
//     unsigned long long tmp;
//     tmp = sched_clock();
// ... ... (do stuff) ...
//     // Displays: "someFunct() complete in: xxxx ns (xx ms).[\n]"
//     showTimeSpent("--------------| someFunct() complete in", tmp); 
// }
