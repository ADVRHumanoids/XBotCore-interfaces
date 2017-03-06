/*
 * Copyright (C) 2017 IIT-ADVR
 * Author: Alessio Margan, Arturo Laurenzi, Luca Muratore
 * email:  arturo.laurenzi@iit.it, luca.muratore@iit.it
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#ifndef __X_BOT_ESC_H__
#define __X_BOT_ESC_H__

#include <stdint.h>

namespace XBot {

struct McEscPdoTypes {
                    
    // TX  slave_input -- master output
    struct pdo_tx {
        float       pos_ref;      
        int16_t     vel_ref;    
        int16_t     tor_ref;    
        uint16_t    gain_0;      
        uint16_t    gain_1;     
        uint16_t    gain_2;     
        uint16_t    gain_3;     
        uint16_t    gain_4;     
        uint16_t    fault_ack;
        uint16_t    ts;
        uint16_t    op_idx_aux;  
        float       aux;         

    } pdo_data_tx __attribute__ ( ( __packed__ ) ); // 28 bytes

    // RX  slave_output -- master input
    struct pdo_rx {
        float        link_pos;          
        float        motor_pos;         
        int16_t      link_vel;          
        int16_t      motor_vel;         
        float        torque;            
        uint16_t     temperature;       
        uint16_t     fault;
        uint16_t     rtt;               
        uint16_t     op_idx_ack;        
        float        aux;               

    } pdo_data_rx __attribute__ ( ( __packed__ ) ); // 28 bytes

}; // 56 bytes

struct Ft6EscPdoTypes {
    
    // TX  slave_input -- master output
    struct pdo_tx {
        uint16_t    ts;
        
    }  __attribute__ ( ( __packed__ ) );

    // RX  slave_output -- master input
    struct pdo_rx {
        float       force_X;            // N
        float       force_Y;            // N
        float       force_Z;            // N
        float       torque_X;           // Nm
        float       torque_Y;           // Nm
        float       torque_Z;           // Nm
        uint16_t    fault;
        uint16_t    rtt;                // ns
        
    }  __attribute__ ( ( __packed__ ) );

};

struct sdo_info {
    float min_pos;
    float max_pos;
    uint16_t ctrl_status_cmd;
};

}


#endif /* __X_BOT_ESC_H__ */
