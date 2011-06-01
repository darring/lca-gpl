import os
import ConfigParser as configparser

def setup_conf(conf_file):
    config = configparser.RawConfigParser()
    if os.path.isfile(conf_file):
        config.read(conf_file)
    else:
        # No file exists, make a sensible default
        config.add_section('main')
        config.set('main', 'log_level', '4')
        config.set('main', 'sleep_timer', '30')
        config.set('main', 'registration_attempts', '10')

        # Writing our configuration file to 'example.cfg'
        with open(conf_file, 'wb') as configfile:
            config.write(configfile)
            configfile.close()

    return config

# vim:set ai et sts=4 sw=4 tw=80:
