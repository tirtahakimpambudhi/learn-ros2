from setuptools import find_packages, setup

package_name = 'python_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='thpdev',
    maintainer_email='thpdev@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            "hello_world = python_pkg.hello_world:main",
            "counter = python_pkg.counter:main",
            "temperature_sensor = python_pkg.temperature_sensor:main",
            "subscriber_temperature_sensor = python_pkg.subscriber_temperature_sensor:main",
            "service_server = python_pkg.service_server:main",
            "service_client = python_pkg.service_client:main",
            "srv_client = python_pkg.srv_client:main", 
            "publish_hardware_status = python_pkg.publish_hardware_status:main",
            "subscriber_hardware_status = python_pkg.subscriber_hardware_status:main",
            "rectangle_area = python_pkg.rectangle_area:main"
        ],
    },
)
