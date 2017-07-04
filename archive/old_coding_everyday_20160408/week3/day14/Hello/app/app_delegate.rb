class AppDelegate

  def hello_world_label
    @hello_world_label ||= begin
                             frame = CGRectMake(20,200,280,40)
                             label           = UILabel.alloc.initWithFrame(frame)
                             label.text      = "Hello world"
                             label.textColor = UIColor.whiteColor
                             label.textAlignment = UITextAlignmentCenter
                             label
                           end
  end

  def window
    @window ||= UIWindow.alloc.initWithFrame(UIScreen.mainScreen.bounds)
  end

  # def application(application, didFinishLaunchingWithOptions:launchOptions)
  #   rootViewController = UIViewController.alloc.init
  #   rootViewController.title = 'Hello'
  #   rootViewController.view.backgroundColor = UIColor.whiteColor

  #   navigationController = UINavigationController.alloc.initWithRootViewController(rootViewController)

  #   # @window = UIWindow.alloc.initWithFrame(UIScreen.mainScreen.bounds)
  #   # @window.rootViewController = navigationController
  #   # @window.makeKeyAndVisible

  #   # @doc: example1
  #   # alert = UIAlertView.new
  #   # alert.message = "Hello World"
  #   # alert.show

  #   # @doc: example2
  #   # @blue_view = UIView.alloc.initWithFrame(CGRectMake(10, 10, 100, 100))

  #   window.addSubview(hello_world_label)
  #   window.rootViewController = navigationController
  #   window.makeKeyAndVisible

  #   true
  #
  def navigation_controller
    @navigation_controller ||= UINavigationController.alloc.
      initWithRootViewController(UIViewController.alloc.init)
  end


  def application(application, didFinishLaunchingWithOptions: launchOptions)
    rootViewController = UIViewController.alloc.init
    rootViewController.title = 'Hello'
    # rootViewController.view.backgroundColor = UIColor.whiteColor

    navigationController = UINavigationController.alloc.initWithRootViewController(rootViewController)

    window.rootViewController = navigationController
    window.addSubview(hello_world_label)
    window.makeKeyAndVisible
    true
  end
end
