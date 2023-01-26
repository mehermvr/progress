//         ##### ##
//      ######  /###
//     /#   /  /  ###
//    /    /  /    ###
//        /  /      ##
//       ## ##      ## ###  /###     /###     /###    ###  /###     /##       /###     /###
//       ## ##      ##  ###/ #### / / ###  / /  ###  / ###/ #### / / ###     / #### / / #### /
//     /### ##      /    ##   ###/ /   ###/ /    ###/   ##   ###/ /   ###   ##  ###/ ##  ###/
//    / ### ##     /     ##       ##    ## ##     ##    ##       ##    ### ####     ####
//       ## ######/      ##       ##    ## ##     ##    ##       ########    ###      ###
//       ## ######       ##       ##    ## ##     ##    ##       #######       ###      ###
//       ## ##           ##       ##    ## ##     ##    ##       ##              ###      ###
//       ## ##           ##       ##    ## ##     ##    ##       ####    /  /###  ## /###  ##
//       ## ##           ###       ######   ########    ###       ######/  / #### / / #### /
//  ##   ## ##            ###       ####      ### ###    ###       #####      ###/     ###/
// ###   #  /                                      ###
//  ###    /                                 ####   ###
//   #####/                                /######  /#
//     ###                                /     ###/
// Have fun. Don't forget to bookmark http://www.network-science.de/ascii/ :)
//
// The bar must be used when there's no other possible source of output
// inside the for loop
//
// TODO: can use the destructor to also output time perf.
#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace progress {

class Progress {
public:
    struct Iterator {
        /**
         * @brief Construct a new Iterator object for a Progress object.
         *
         * @param ptr Pointer to the private counter attribute of the Progress object
         * @param bar a reference to the progress bar itself
         */
        Iterator(int *ptr, Progress &bar) : m_ptr(ptr), m_progress(bar) {}

        // necessary operators
        int &operator*() const { return *m_ptr; }
        int *operator->() { return m_ptr; }
        /**
         * @brief the main operator that does the heavy lifting. calls push() on the progress
         *
         * @return Iterator&
         */
        Iterator &operator++();
        /**
         * @brief Responsible for terminating the loop. Take note that ill-defing the left and right
         * will lead to failure. It doesnt have much in the way of error checking.
         *
         * @param left the begin iterator (ideally)
         * @param right the end iterator (ideally) whose m_ptr should be nullptr (ideally)
         * @return true continue the loop
         * @return false terminate the loop
         */
        friend bool operator!=(const Iterator &left, const Iterator &right);

    private:
        // should be a pointer to the progress bar counter
        int *m_ptr{nullptr};
        Progress &m_progress;
    };

    /**
     * @brief Construct a new Progress object
     *
     * @param total Number of increments. max counter value will be total - 1
     * @param ostream std::ostream object to write to
     */
    explicit Progress(int total, std::ostream &ostream = std::cout);

    /**
     * @brief Construct a new Progress object
     *
     * @param total Number of increments. max counter value will be total - 1
     * @param ticks total number of times the progress bar will be updated/printed in the full loop.
     * This will be useful when the loop is quite short and the printing becomes the bottleneck of
     * performace
     * @param ostream std::ostream object to write to
     */
    Progress(int total, int ticks, std::ostream &ostream = std::cout);

    /**
     * @brief Destroy the Progress object. By default calls keep() to print a new line at the end.
     *
     */
    ~Progress() { keep(); };

    Progress(Progress const &) = delete;
    Progress &operator=(Progress const &) = default;
    Progress(Progress &&) = delete;
    Progress &operator=(Progress &&) = delete;

    /**
     * @brief Update the internal counter based on update().
     *
     * default is 1. Then prints the progress bar/counter to the ostream.
     */
    void push();

    /**
     * @brief just a print of std::endl to ostream.
     *
     */
    void keep();

    /**
     * @brief is the internal counter == total (set on construction)
     *
     * @return true yes, so you can terminate the loop
     * @return false no, so continue the loop
     */
    bool finished() const { return m_counter < m_total; }

    /**
     * @brief returns an iterator that points to the current value of the internal counter.
     *
     * @return Iterator
     */
    Iterator begin() { return {&m_counter, *this}; }

    /**
     * @brief returns an iterator that essentially points to nullptr.
     *
     * shouldn't really need to use this.
     * @return Iterator
     */
    Iterator end() { return {nullptr, *this}; }

    // named parameters

    /**
     * @brief Set the ticks of the bar.
     *
     * This is the number of times the bar is written to the ostream. For example if total is 1000,
     * and ticks is 100, then the bar is written every 100 increments to counter. So when counter =
     * 100, 200, ...
     *
     * @param ticks_
     * @return Progress&
     */
    Progress &ticks(int ticks_);

    /**
     * @brief Set how much the counter should be incremented each time. Default 1
     *
     * @param count value to update the internal counter by
     * @return Progress&
     */
    Progress &update(int count);

    /**
     * @brief Flag to control the display of the bar.
     *
     * @param show if true, the bar is shown as per the style. Default true
     * @return Progress&
     */
    Progress &show_bar(bool show);

    /**
     * @brief The length of the bar part of the progress bar in characters. Default 20.
     *
     * @param bar_length length in characters
     * @return Progress&
     */
    Progress &length(int bar_length);

    /**
     * @brief Style of the bar display. Should be a string of 4 characters.
     *
     * Default [# ], which means the opening character is [, the character for percentage done is #,
     * the remaining part character ' ' and the closing character is ]. Can't really handle the
     * larger unicode character set i think. Maybe I'll imporve on that in the future.
     *
     * @param style
     * @return Progress&
     */
    Progress &style(std::string_view style);

    /**
     * @brief the name of the progress bar/counter. Printed first to the left of the line.
     *
     * @param name string. whatever you want.
     * @return Progress&
     */
    Progress &name(std::string_view name);

private:
    int m_total{};
    int m_counter{};
    int m_update{1};
    int m_ticks{};
    int m_next_tick{};
    bool m_show_bar{true};
    int m_bar_length{20};
    std::string m_style{"[# ]"};
    std::string m_name{"Progress"};

    std::ostream &m_output{std::cout};
};

inline Progress::Progress(int total, std::ostream &ostream)
    : m_total(total), m_ticks(total), m_output(ostream) {}
inline Progress::Progress(int total, int ticks, std::ostream &ostream)
    : m_total(total), m_ticks(ticks), m_output(ostream) {}

inline void Progress::push() {
    m_counter += m_update;
    int current_tick = std::floor(m_counter * static_cast<double>(m_ticks) / m_total);
    if (current_tick < m_next_tick) {
        return;
    }
    m_next_tick = current_tick + 1;

    std::stringstream percstr;
    percstr << std::setw(4) << std::floor(current_tick * 100. / m_ticks) << "%";

    m_output << ' ' << m_name << " : ";
    if (m_show_bar) {
        m_output << m_style[0];
        std::string donebar(m_bar_length, m_style[2]);
        donebar.replace(0, std::floor(current_tick * static_cast<double>(m_bar_length) / m_ticks),
                        std::floor(current_tick * static_cast<double>(m_bar_length) / m_ticks),
                        m_style[1]);
        m_output << donebar;
        m_output << m_style[3];
    }
    m_output << ' ' << m_counter << " / " << m_total;
    m_output << ' ' << percstr.str();
    m_output << '\r';
    m_output << std::flush;
}

inline void Progress::keep() { m_output << std::endl; }

inline Progress &Progress::ticks(int ticks_) {
    m_ticks = ticks_;
    return *this;
}

inline Progress &Progress::update(int count) {
    m_update = count;
    return *this;
}

inline Progress &Progress::show_bar(bool show) {
    m_show_bar = show;
    return *this;
}

inline Progress &Progress::length(int bar_length) {
    m_bar_length = bar_length;
    return *this;
}

inline Progress &Progress::style(std::string_view style) {
    m_style = style;
    return *this;
}

inline Progress &Progress::name(std::string_view name) {
    m_name = name;
    return *this;
}

inline Progress::Iterator &Progress::Iterator::operator++() {
    // dont increment the end Iterator
    if (m_ptr != nullptr) {
        m_progress.push();
    }
    return *this;
}

inline bool operator!=(const Progress::Iterator &left, const Progress::Iterator &right) {
    if (left.m_ptr != nullptr && right.m_ptr == nullptr) {
        return left.m_progress.finished();
    }
    throw std::runtime_error("you're on your own");
};
}  // namespace progress