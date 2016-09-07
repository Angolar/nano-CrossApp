

#ifndef __CANotificationCenter_H__
#define __CANotificationCenter_H__

#include "basics/CAObject.h"
#include "basics/CASTLContainer.h"

NS_CC_BEGIN

/**
 * @js NA
 * @lua NA
 */
class CC_DLL CANotificationObserver : public CAObject
{
public:
    /** @brief CANotificationObserver constructor
     *  @param target The target which wants to observer notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param obj The extra parameter which will be passed to the callback function.
     */
    CANotificationObserver(CAObject *target,
                           SEL_CallFuncO selector,
                           const std::string& name,
                           CAObject *obj);
    
    /** CANotificationObserver destructor function */
    ~CANotificationObserver();
    
    /** Invokes the callback function of this observer */
    void performSelector(CAObject *obj);
private:
    CC_PROPERTY_READONLY(CAObject *, m_target, Target);
    CC_PROPERTY_READONLY(SEL_CallFuncO, m_selector, Selector);
    CC_PROPERTY_READONLY_PASS_BY_REF(std::string, m_name, Name);
    CC_PROPERTY_READONLY(CAObject *, m_object, Object);
    CC_PROPERTY(int, m_nHandler,Handler);
};

/**
 * @js NA
 */
class CC_DLL CANotificationCenter : public CAObject
{
public:
    /** CANotificationCenter constructor */
    CANotificationCenter();

    /** CANotificationCenter destructor */
    ~CANotificationCenter();
    
    /** Gets the single instance of __NotificationCenter. */
    static CANotificationCenter *getInstance();
    
    /** Destroys the single instance of __NotificationCenter. */
    static void destroyInstance();
    
    /** @deprecated use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static CANotificationCenter *sharedNotificationCenter(void)
    {
        return CANotificationCenter::getInstance();
    }
    
    /** @deprecated use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeNotificationCenter(void)
    {
        CANotificationCenter::destroyInstance();
    }

    /** @brief Adds an observer for the specified target.
     *  @param target The target which wants to observe notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param obj The extra parameter which will be passed to the callback function.
     */
    void addObserver(CAObject *target, 
                     SEL_CallFuncO selector,
                     const std::string& name,
                     CAObject *obj);

    /** @brief Removes the observer by the specified target and name.
     *  @param target The target of this notification.
     *  @param name The name of this notification. 
     */
    void removeObserver(CAObject *target,const std::string& name);
    
    /** @brief Removes all notifications registered by this target
     *  @param target The target of this notification.
     *  @returns the number of observers removed
     */
    int removeAllObservers(CAObject *target);

    /** @brief Registers one hander for script binding.
     *  @note Only supports Lua Binding now.
     *  @param handler The lua handler.
     */
    void registerScriptObserver(CAObject *target, int handler, const std::string& name);

    /** Unregisters script observer */
    void unregisterScriptObserver(CAObject *target, const std::string& name);
    
    /** @brief Posts one notification event by name.
     *  @param name The name of this notification.
     */
    void postNotification(const std::string& name);

    /** @brief Posts one notification event by name.
     *  @param name The name of this notification.
     *  @param object The extra parameter.
     */
    void postNotification(const std::string& name, CAObject *object);
    
    /** @brief Gets script handler.
     *  @note Only supports Lua Binding now.
     *  @return The script handle.
     */
    inline int getScriptHandler() { return m_scriptHandler; };
    
    /** @brief Gets observer script handler.
     *  @param name The name of this notification.
     *  @return The observer script handle.
     */
    int getObserverHandlerByName(const std::string& name);
private:
    // internal functions

    // Check whether the observer exists by the specified target and name.
    bool observerExisted(CAObject *target, const std::string& name);
    
    // variables
    //
    CADeque<CANotificationObserver*> m_observers;
    int     m_scriptHandler;
};



NS_CC_END

#endif//__CANotificationCenter_H__
