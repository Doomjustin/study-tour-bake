#ifndef STUDY_TOUR_CONCEPT_H
#define STUDY_TOUR_CONCEPT_H

#include <type_traits>


namespace ST {

template<typename T>
concept EnumType = std::is_enum_v<T>;

} // namespace ST

#endif // STUDY_TOUR_CONCEPT_H