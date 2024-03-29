// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// (C) Copyright 2009-2012 Anthony Williams
// (C) Copyright 2012 Vicente J. Botet Escriba

// Based on the Anthony's idea of scoped_thread in CCiA

#ifndef BOOST_THREAD_SCOPED_THREAD_HPP
#define BOOST_THREAD_SCOPED_THREAD_HPP

#include <boost/thread/detail/config.hpp>
#include <boost/thread/detail/delete.hpp>
#include <boost/thread/detail/move.hpp>
#include <boost/thread/thread_functors.hpp>
#include <boost/thread/thread.hpp>

#include <boost/config/abi_prefix.hpp>

namespace boost
{

  /**
   * RAI @c thread wrapper adding a specific destroyer allowing to master what can be done at destruction time.
   *
   * CallableThread: A callable void(thread&) .
   * The default is a join_if_joinable.
   *
   * thread std/boost::thread destructor terminates the program if the thread is not joinable.
   * Having a wrapper that can join the thread before destroying it seems a natural need.
   *
   * Example:
   *
   *     boost::strict_scoped_thread<> t((boost::thread(F)));
   *
   */
  template <class CallableThread = join_if_joinable>
  class strict_scoped_thread
  {
    thread t_;
  public:

    BOOST_THREAD_NO_COPYABLE( strict_scoped_thread) /// non copyable

    /**
     * Constructor from the thread to own.
     *
     * @param t: the thread to own.
     *
     * Effects: move the thread to own @c t.
     */
    explicit strict_scoped_thread(BOOST_THREAD_RV_REF(thread) t) :
    t_(boost::move(t))
    {
    }

    /**
     * Destructor
     */
    ~strict_scoped_thread()
    {
      CallableThread on_destructor;

      on_destructor(t_);
    }

  };

  /**
   * RAI @c thread wrapper adding a specific destroyer allowing to master what can be done at destruction time.
   *
   * CallableThread: A callable void(thread&) .
   * The default is join_if_joinable.
   *
   * thread std::thread destructor terminates the program if the thread is not joinable.
   * Having a wrapper that can join the thread before destroying it seems a natural need.
   *
   * Remark: @c scoped_thread is not a @c thread as @c thread is not designed to be derived from as a polymorphic type.
   * Anyway @c scoped_thread can be used in most of the contexts a @c thread could be used as it has the
   * same non-deprecated interface with the exception of the construction.
   *
   * Example:
   *
   *     boost::scoped_thread<> t((boost::thread(F)));
   *     t.interrupt();
   *
   */
  template <class CallableThread = join_if_joinable>
  class scoped_thread
  {
    thread t_;
  public:

    typedef thread::id id;

    BOOST_THREAD_MOVABLE_ONLY( scoped_thread) /// Movable only

    /**
     * Default Constructor.
     *
     * Effects: wraps a not-a-thread.
     */
    scoped_thread() BOOST_NOEXCEPT:
    t_()
    {
    }

    /**
     * Constructor from the thread to own.
     *
     * @param t: the thread to own.
     *
     * Effects: move the thread to own @c t.
     */
    explicit scoped_thread(BOOST_THREAD_RV_REF(thread) t) :
    t_(boost::move(t))
    {
    }

//    explicit operator thread()
//    {
//      return boost::move(t_);
//    }

    /**
     * Move constructor.
     */
    scoped_thread(BOOST_RV_REF(scoped_thread) x) :
    t_(boost::move(x.t_))
    {}

    /**
     * Destructor
     *
     * Effects: destroys the internal destroyer before destroying the owned thread.
     */
    ~scoped_thread()
    {
      CallableThread on_destructor;

      on_destructor(t_);
    }

    /**
     * Move assignment.
     */
    scoped_thread& operator=(BOOST_RV_REF(scoped_thread) x)
    {
      t_ = boost::move(x.t_);
      return *this;
    }

    /**
     *
     */
    void swap(scoped_thread& x)BOOST_NOEXCEPT
    {
      t_.swap(x.t_);
    }

    // forwarded thread functions
    inline thread::id get_id() const BOOST_NOEXCEPT
    {
      return t_.get_id();
    }

    void detach()
    {
      t_.detach();
    }

    void join()
    {
      t_.join();
    }

#ifdef BOOST_THREAD_USES_CHRONO
    template <class Rep, class Period>
    bool try_join_for(const chrono::duration<Rep, Period>& rel_time)
    {
      return t_.try_join_for(rel_time);
    }

    template <class Clock, class Duration>
    bool try_join_until(const chrono::time_point<Clock, Duration>& abs_time)
    {
      return t_.try_join_until(abs_time);
    }
#endif

    thread::native_handle_type native_handle()BOOST_NOEXCEPT
    {
      return t_.native_handle();
    }

#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
    void interrupt()
    {
      t_.interrupt();
    }

    bool interruption_requested() const BOOST_NOEXCEPT
    {
      return t_.interruption_requested();
    }
#endif

    static unsigned hardware_concurrency()BOOST_NOEXCEPT
    {
      return thread::hardware_concurrency();
    }

  };

  /**
   * Effects: swaps the contents of two scoped threads.
   */
  template <class Destroyer>
  void swap(scoped_thread<Destroyer>& lhs, scoped_thread<Destroyer>& rhs)
BOOST_NOEXCEPT {
  return lhs.swap(rhs);
}

}
#include <boost/config/abi_suffix.hpp>

#endif
