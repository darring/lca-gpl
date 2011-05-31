import os
import ConfigParser as configparser

def setup_config(conf_file):
    config = configparser.RawConfigParser()
    if os.path.isfile(conf_file):
        config.read(conf_file)
    else:
        # No file exists, make a sensible default
        config.add_section('main')
        config.set('main', 'log_level', '3')
        config.set('main', 'sleep_timer', '30')

        # Writing our configuration file to 'example.cfg'
        with open(config_file, 'wb') as configfile:
            config.write(configfile)

    return config

# vim:set ai et sts=4 sw=4 tw=80: