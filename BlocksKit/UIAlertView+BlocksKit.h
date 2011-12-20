//
//  UIAlertView+BlocksKit.h
//  %PROJECT
//

#import "BKGlobals.h"

/** UIAlertView without delegates!

 This set of extensions and convenience classes allows
 for an instance of UIAlertView without the implementation
 of a delegate.  Any time you instantiate a UIAlertView
 using the methods here, you must add buttons using
 addButtonWithTitle:handler: otherwise nothing will happen.

 A typical invocation will go like this:
	 UIAlertView *testView = [UIAlertView alertViewWithTitle:@"Application Alert" message:@"This app will explode in 42 seconds."];
	 [testView setCancelButtonWithTitle:@"Oh No!" handler:^{ NSLog(@"Boom!"); }];
	 [testView show];

 A more traditional, and more useful, modal dialog looks like so:
	UIAlertView *testView = [UIAlertView alertViewWithTitle:@"Very important!" message:@"Do you like chocolate?"];
	[testView addButtonWithTitle:@"Yes" handler:^{ NSLog(@"Yay!"); }];
	[testView addButtonWithTitle:@"No" handler:^{ NSLog(@"We hate you."); }];
	[testView show];

 Includes code by the following:

 - Landon Fuller, "Using Blocks".  <http://landonf.bikemonkey.org>.
 - Peter Steinberger. <https://github.com/steipete>.   2011. MIT.
 - Zach Waldowski.	<https://github.com/zwaldowski>. 2011. MIT.

 @warning UIAlertView is only available on iOS or in a Mac app using Chameleon.
 */
@interface UIAlertView (BlocksKit)

///-----------------------------------
/// @name Creating alert views
///-----------------------------------

/** Creates and shows a new alert view with only a title, message, and cancel button.
 
 @param title The title of the alert view.
 @param message The message content of the alert.
 @param block A block of code to be fired on the dismissal of the alert view.
 @param buttonText The text of the single button.  If empty or nil, defaults to a localized variant of "Dismiss".
 @param cancelButtonTitle The title of the cancel button or nil if there is no cancel button.
 @param otherButtonTitles, The title of another button.
 @param ... Titles of additional buttons to add to the receiver, terminated with nil.
 */
+ (void) showAlertViewWithTitle: (NSString *) title message: (NSString *) message didDismissHandler: (void (^)(UIAlertView *, NSInteger)) block cancelButtonTitle: (NSString *) cancelButtonTitle otherButtonTitles: (NSString *) otherButtonTitles, ... NS_REQUIRES_NIL_TERMINATION;

/** Creates and returns a new alert view with only a title and cancel button.

 @param title The title of the alert view.
 @return A newly created alert view.
 */
+ (id)alertViewWithTitle:(NSString *)title;

/** Creates and returns a new alert view with only a title, message, and cancel button.

 @param title The title of the alert view.
 @param message The message content of the alert.
 @return A newly created alert view.
 */
+ (id)alertViewWithTitle:(NSString *)title message:(NSString *)message;

/** Returns a configured alert view with only a title, message, and cancel button.
 
 @param title The title of the alert view.
 @param message The message content of the alert.
 @return An instantiated alert view.
 */
- (id)initWithTitle:(NSString *)title message:(NSString *)message;

///-----------------------------------
/// @name Adding buttons
///-----------------------------------

/** Add a new button with an associated code block.
 
 @param title The text of the button.
 @param block A block of code.
 */
- (NSInteger)addButtonWithTitle:(NSString *)title handler:(BKBlock)block;

/** Set the title and trigger of the cancel button.

 `block` can be set to `nil`, but this is generally useless as
 the cancel button is configured already to do nothing.

 @param title The text of the button.
 @param block A block of code.
 */
- (NSInteger)setCancelButtonWithTitle:(NSString *)title handler:(BKBlock)block;

///-----------------------------------
/// @name Altering actions
///-----------------------------------

/** The block that is to be fired when a button is pressed.
 
 @param index The index of the button already added to the alert view.
 @return An instance of a code block, or nil if no block yet assigned.
 */
- (BKBlock)handlerForButtonAtIndex:(NSInteger)index;

/** The block to be fired when the action sheet is dismissed with the cancel
 button.

 This property performs the same action as setCancelButtonWithTitle:handler:
 but with `title` set to nil.  Contrary to setCancelButtonWithTitle:handler:,
 you can set this property multiple times and multiple cancel buttons will
 not be generated.
 */
@property (nonatomic, copy) BKBlock cancelBlock;

/** The block to be fired before the alert view will show. */
@property (nonatomic, copy) void (^willShowBlock)(UIAlertView *);

/** The block to be fired when the alert view shows. */
@property (nonatomic, copy) void (^didShowBlock)(UIAlertView *);

/** The block to be fired before the alert view will dismiss. */
@property (nonatomic, copy) void (^willDismissBlock)(UIAlertView *, NSInteger);

/** The block to be fired after the alert view dismisses. */
@property (nonatomic, copy) void (^didDismissBlock)(UIAlertView *, NSInteger);

/** The block to be fired to determine whether the first non-cancel should be enabled */
@property (nonatomic, copy) BOOL (^shouldEnableFirstOtherButtonBlock)(UIAlertView *) NS_AVAILABLE_IOS(5_0);

@end
