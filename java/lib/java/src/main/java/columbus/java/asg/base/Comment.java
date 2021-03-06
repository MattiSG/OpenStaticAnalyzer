/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

package columbus.java.asg.base;


/**
 * Interface Comment, which represents the {@link columbus.java.asg.base.Comment Comment} node.
 * @columbus.node (missing)
 * @columbus.attr text (String) : (missing)
 */
public interface Comment extends PositionedWithoutComment {

	/**
	 * Gives back the {@link columbus.java.asg.base.Comment#attributeText text} of the node.
	 * @return Returns with the text.
	 */
	public String getText();

	/**
	 * Gives back the Key of {@link columbus.java.asg.base.Comment#attributeText text} of the node.
	 * @return Returns with the Key of the text.
	 */
	public int getTextKey();

	/**
	 * Sets the {@link columbus.java.asg.base.Comment#attributeText text} of the node.
	 * @param value The new value of the text.
	 */
	public void setText(String value);

}

