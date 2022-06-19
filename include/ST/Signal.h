#ifndef STUDY_TOUR_SIGNAL_H
#define STUDY_TOUR_SIGNAL_H


namespace ST {

typedef void Sigfunc(int);

Sigfunc* Signal(int signo, Sigfunc* func);

} // namespace ST

#endif // STUDY_TOUR_SIGNAL_H