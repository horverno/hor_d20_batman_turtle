#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "turtlesim/msg/pose.hpp"

class BatmanDraw : public rclcpp::Node
{
public:
    BatmanDraw() : Node("batman_draw"), count_(0)
    {
        // auto sub_options = rclcpp::SubscriptionOptions();
        // timer_cb_group_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
        // subsc_cb_group_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
        // sub_options.callback_group = subsc_cb_group_;
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        // subscriber_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, std::bind(&BatmanDraw::pose_callback, this, std::placeholders::_1)); //sub_options
        timer_ = this->create_wall_timer(std::chrono::milliseconds(1), std::bind(&BatmanDraw::loop, this)); //timer_cb_group_
        RCLCPP_INFO_STREAM(this->get_logger(), "Drawing a batman logo to turtlsesim.");
        loop();
    }

private:
    // void pose_callback(const turtlesim::msg::Pose::SharedPtr msg)
    // {
    //     RCLCPP_INFO_STREAM(this->get_logger(), "X " << msg->x << " Y " << msg->y << " Theta " << msg->theta);
    //     x = msg->x;
    //     y = msg->y;
    //     theta = msg->theta;
    // }
    void publish_message(double fwd, double turn)
    {
        auto message = geometry_msgs::msg::Twist();
        message.linear.x = fwd;
        message.angular.z = turn;
        count_++;
        RCLCPP_INFO(this->get_logger(), "Step %ld. speed: '%.1f' turn: '%.1f'", count_, message.linear.x, message.angular.z);
        publisher_->publish(message);
        // delay for 2 second
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // RCLCPP_INFO_STREAM(this->get_logger(), "X: " << x << " Y: " << y << " Theta: " << theta);
    }
    void loop()
    {
        RCLCPP_INFO_STREAM(this->get_logger(), "Loop started.");
        std::this_thread::sleep_for(std::chrono::seconds(2)); // delay for 2 second
        publish_message(0.0, M_PI_2);                         // rotate 90 degrees
        publish_message(M_PI_2, -1 * M_PI_2);                 // turn right and move forward
        publish_message(0.0, M_PI_2);
        publish_message(M_PI_2, -1 * M_PI_2); // turn right and move forward
        publish_message(0.0, M_PI);           // rotate 180 degrees
        publish_message(4.06, 0.0);            // move forward

        publish_message(0.0, M_PI);           // rotate
        publish_message(M_PI_2, -1 * M_PI_2); // turn right and move forward
        publish_message(0.0, M_PI_2);
        publish_message(M_PI_2, -1 * M_PI_2); // turn right and move forward
        publish_message(0.0, M_PI);           // rotate

        RCLCPP_INFO_STREAM(this->get_logger(), "Program finished");
        rclcpp::shutdown();
    }

    rclcpp::TimerBase::SharedPtr timer_;
    // rclcpp::CallbackGroup::SharedPtr timer_cb_group_, subsc_cb_group_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;
    double x, y, theta;
    size_t count_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BatmanDraw>());
    rclcpp::shutdown();
    return 0;
}